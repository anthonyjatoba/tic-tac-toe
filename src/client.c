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
  char nome_jogador[20];
  char peca, peca_oponente;
  int coordenada;
  int my_turn = 0;
  int end = 0;

  buf = (char *) calloc (MAXDATASIZE, sizeof(char));
	_buf = (char *) calloc (MAXDATASIZE, sizeof(char));
	message = (char *) calloc (MAXDATASIZE, sizeof(char));

  system("clear");

  if (argc == 2)
    if ((he=gethostbyname(argv[1])) == NULL)
      gethostbyname_error();

  if ((socket_local = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	  socket_error();

  endereco_remoto.sin_family = AF_INET;
  endereco_remoto.sin_port = htons(PORTA);
  endereco_remoto.sin_addr = *((struct in_addr *)he->h_addr);
  bzero(&(endereco_remoto.sin_zero), 8);

  if (connect(socket_local, (struct sockaddr *)&endereco_remoto, sizeof(struct sockaddr)) == -1)
	  connect_error();

  printf("Digite seu nome: ");
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
    printf("A sala está cheia, tente novamente mais tarde\n");
    exit(0);
  } else {
    strcpy(_buf, buf);
    peca = get_value(_buf)[0];
    printf("Olá, %s!\nVocê vai jogar com a peça %c\n", nome_jogador, peca);
    if (peca == 'x')
      peca_oponente = 'o';
    else
      peca_oponente = 'x';
  }

  printf("Antes de receber o ready\n");

  //Aguarda o jogo estar pronto (2 jogadores)
  do{
    if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
      recv_error();
    buf[num_bytes] = '\0';
  } while(strcmp(buf, "READY") != 0);

  printf("Recebi a mensagem %s\n", buf);
  sleep(3);

  //X começa
  if (peca == 'x')
    my_turn = 1;

  do{
    system("clear");
    printf("Nome: %s\t\tPeça: %c\n\n", nome_jogador, peca);
    imprime(tabuleiro);

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
      fflush(stdin);
      do{
        printf("Digite a coordenada da sua jogada: \n");
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
      printf("Espere o outro jogador\n");

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

}
