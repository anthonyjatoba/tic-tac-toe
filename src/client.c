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
    int socket_local;
    char buf[MAXDATASIZE], _buf[MAXDATASIZE];
    int num_bytes;

    struct hostent * he = gethostbyname("localhost");
    struct sockaddr_in endereco_remoto;

    char nome_jogador[20];

    system("clear");

    //tá feio isso aqui
    if (argc == 2){
      if ((he=gethostbyname(argv[1])) == NULL) {
        herror("gethostbyname");
        exit(1);
      }
    }

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
    fflush(stdin);

    //START
    if(send(socket_local, generate_message(START, nome_jogador), MAXDATASIZE, 0) == -1)
      send_error();

    //Recebe o WELCOME
    if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
      recv_error();
    buf[num_bytes] = '\0';
    fflush(stdin);

    strcpy(_buf, buf);

    if (get_message_type(_buf) != WELCOME){
      printf("A sala está cheia, tente novamente mais tarde\n");
      exit(0);
    } else {
      strcpy(_buf, buf);
      char peca = get_value(_buf)[0];
      printf("Você vai jogar com a peça %c\n", peca);
    }
    
    while(1){
      sleep(1);
    }

}
