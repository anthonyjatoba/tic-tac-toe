#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "headers/error.h"
#include "headers/jogador.h"
#include "headers/message.h"
#include "headers/gui.h"

#define PORTA       12345
#define MAXDATASIZE 100

void main(int argc, char *argv[]){

  //Variáveis de rede
  int socket_local;
  struct sockaddr_in endereco_remoto;
  struct hostent * he = gethostbyname("localhost");
  char *buf, *_buf, *message;
  int num_bytes;

  //Variáveis do jogo
  char tabuleiro[] = "         ";
  char *nome_jogador;
  char peca, peca_oponente;
  int coordenada;
  int my_turn = 0;
  int end = 0;
  int opc;

  buf = (char *) calloc (MAXDATASIZE, sizeof(char));
	_buf = (char *) calloc (MAXDATASIZE, sizeof(char));
	message = (char *) calloc (MAXDATASIZE, sizeof(char));
  nome_jogador = (char *) calloc (20, sizeof(char));

  if (argc == 2)
    if ((he=gethostbyname(argv[1])) == NULL)
      gethostbyname_error();

  if ((socket_local = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	  socket_error();

  endereco_remoto.sin_family = AF_INET;
  endereco_remoto.sin_port = htons(PORTA);
  endereco_remoto.sin_addr = *((struct in_addr *)he->h_addr);
  memset(endereco_remoto.sin_zero, 0, 8);

  if (connect(socket_local, (struct sockaddr *)&endereco_remoto, sizeof(struct sockaddr)) == -1)
	  connect_error();


  do{
      print_menu();
      scanf("%d", &opc);
      if (opc == 1){
          print_setup();
          scanf(" %[^\n]", nome_jogador);

          //START
          if(send(socket_local, generate_message(START, nome_jogador), MAXDATASIZE, 0) == -1)
            send_error();

          //Recebe o WELCOME
          if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
            recv_error();
          buf[num_bytes] = '\0';
          strcpy(_buf, buf);

          if (get_message_type(_buf) != WELCOME){
            printf("\n A sala está cheia, tente novamente mais tarde\n");
            exit(0);
          } else {
            strcpy(_buf, buf);
            peca = get_value(_buf)[0];
            printf("\n Olá, %s! Você vai jogar com %c\n\n", nome_jogador, peca);
            printf(" Aguarde a entrada do outro jogador\n");
            if (peca == 'x')
              peca_oponente = 'o';
            else
              peca_oponente = 'x';
          }

          //Aguarda o jogo estar pronto (2 jogadores)
          do{
            if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
              recv_error();
            buf[num_bytes] = '\0';
          } while(strcmp(buf, "READY") != 0);

          //X começa
          if (peca == 'x')
            my_turn = 1;

          do{
            print_tela_jogo(tabuleiro, nome_jogador, peca, "provisório", peca_oponente);

            if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
              recv_error();
            buf[num_bytes] = '\0';

            if (get_message_type(buf) == WIN){
              printf("Você venceu!\n");
              break;
            } else if (get_message_type(buf) == LOSE){
              printf("Você perdeu!\n");
              break;
            } else if (get_message_type(buf) == TIE){
              printf("Deu velha!\n");
              break;
            }

            //Minha vez
            if (my_turn){
              do{
                printf(" Digite a coordenada da sua jogada: ");
                scanf("%d", &coordenada);
              } while (!validar_jogada(tabuleiro, coordenada));

              sprintf(message, "MOVE %d", coordenada);

              if(send(socket_local, message, MAXDATASIZE, 0) == -1)
                send_error();

              //Recebe o VALID_MOVE, inverte o my_turn
              if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
                recv_error();
              buf[num_bytes] = '\0';

              strcpy(_buf, buf);

              if (get_message_type(buf) == VALID_MOVE){
                tabuleiro[coordenada-1] = peca;
                my_turn = 0;
              }

            } else {
              printf(" Espere o outro jogador\n");

              if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
                recv_error();
              buf[num_bytes] = '\0';
              strcpy(_buf, buf);

              if (get_message_type(_buf) == OPPONENT_MOVED){
                coordenada = atoi(get_value(buf));
                tabuleiro[coordenada-1] = peca_oponente;
                my_turn = 1;
              }

            }
          } while(end != 1);

      } else if (opc == 2){
        print_ajuda();
      }
  }while (opc != 3);

}
