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
#include "headers/mensagem.h"
#include "headers/ui.h"

#define PORTA       12345
#define MAXDATASIZE 100

void main(int argc, char *argv[]) {
  //Variáveis de rede
  int socket_local;
  struct sockaddr_in endereco_remoto;
  struct hostent * he = gethostbyname("localhost");
  char *buf, *_buf, *mensagem;
  int num_bytes;

  //Variáveis do jogo
  char tabuleiro[] = "         ";
  char *nome_jogador, *nome_oponente;
  char peca = 'x', peca_oponente = 'o';
  int minha_vez = 0, fim = 0;
  char coordenada;
  char opc = ' ';

  buf = (char *) calloc (MAXDATASIZE, sizeof(char));
  _buf = (char *) calloc (MAXDATASIZE, sizeof(char));
  mensagem = (char *) calloc (MAXDATASIZE, sizeof(char));
  nome_jogador = (char *) calloc (40, sizeof(char));
  nome_oponente = (char *) calloc (40, sizeof(char));

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

  do {
    print_menu();
    fflush(stdin);
    scanf("%c", &opc);
    printf("\n");
    if (opc == '1') {

      print_setup();
      scanf(" %[^\n]", nome_jogador);

      //START
      if(send(socket_local, gerar_mensagem(START, nome_jogador, 0), MAXDATASIZE, 0) == -1)
        send_error();

      //Recebe WELCOME ou FULL_ROOM
      if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
        recv_error();
      buf[num_bytes] = '\0';

      if (get_tipo_mensagem(buf) == WELCOME) {
        strcpy(_buf, buf);
        peca = get_valor(_buf)[0];
        printf("\n Olá, %s! Você vai jogar com %c\n\n", nome_jogador, peca);
        printf(" Aguarde a entrada do outro jogador\n");
        if (peca == 'o')
          peca_oponente = 'x';
      } else {
        printf("\n A sala está cheia, tente novamente mais tarde\n");
        exit(0);
      }

      //Aguarda o jogo estar pronto
      if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
          recv_error();
        buf[num_bytes] = '\0';

      printf("Mensagem >> %s\n", buf);
      printf("Valor >> %s\n", get_valor(buf));
      strcpy(nome_oponente, get_valor(buf));

      //X começa
      if (peca == 'x')
        minha_vez = 1;

      do {
        print_tela_jogo(tabuleiro, nome_jogador, peca, nome_oponente, peca_oponente);

        if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
          recv_error();
        buf[num_bytes] = '\0';

        if (get_tipo_mensagem(buf) == GAME_OVER){
          if (strcmp(get_valor(buf), "WIN") == 0) {
            printf("Você venceu!\n");
            break;
          } else if (strcmp(get_valor(buf), "LOSE") == 0) {
            printf("Você perdeu!\n");
            break;
          } else if (strcmp(get_valor(buf), "TIE") == 0) {
            printf("Deu velha!\n");
            break;
          }
        }

        //Minha vez
        if (minha_vez) {
          do{
            printf(" Digite a coordenada da sua jogada: ");
            scanf(" %[^\n]", &coordenada);
            fflush(stdin);
          } while (!validar_jogada(tabuleiro, coordenada));

          sprintf(mensagem, "MOVE %c", coordenada);

          if(send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
            send_error();

          //Recebe o VALID_MOVE, inverte o minha_vez
          if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
            recv_error();
          buf[num_bytes] = '\0';

          strcpy(_buf, buf);

          if (get_tipo_mensagem(buf) == VALID_MOVE) {
            tabuleiro[(coordenada-48)-1] = peca;
            minha_vez = 0;
          }

        } else {
          printf(" Aguarde o outro jogador fazer sua jogada.\n");

          if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
            recv_error();
          buf[num_bytes] = '\0';
          strcpy(_buf, buf);

          if (get_tipo_mensagem(_buf) == OPPONENT_MOVED) {
            coordenada = atoi(get_valor(buf));
            tabuleiro[coordenada-1] = peca_oponente;
            minha_vez = 1;
          }
        }
      } while(fim != 1);
      sleep(5);
      opc = '3';
    } else if (opc == '2') {
      print_ajuda();
    }
  } while (opc != '3');
  close(socket_local);
}
