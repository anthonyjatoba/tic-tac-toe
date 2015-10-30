#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "headers/error.h"
#include "headers/message.h"
#include "headers/jogador.h"

#define PORTA       12345
#define MAXDATASIZE 100

void main(int argc, char *argv[]){
    int socket_local;
    int num_bytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in endereco_remoto;
    int log_h = 0; //Mensagem passada por parâmetro que habilita a impressão de mensagens

    system("clear");

    he = gethostbyname("localhost");

    if (argc == 2){
      if (!strcmp(argv[1], "log"))
        log_h = 1;
      else
        if ((he=gethostbyname(argv[1])) == NULL)
          gethostbyname_error();
    } else if (argc == 3){
      if ((he=gethostbyname(argv[1])) == NULL)
        gethostbyname_error();
      if (!strcmp(argv[2], "log"))
        log_h = 1;
    }

    //printf("%s\t%d\n", he->h_name, log_h);

    if ((socket_local = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		  socket_error();

    endereco_remoto.sin_family = AF_INET;
    endereco_remoto.sin_port = htons(PORTA);
    endereco_remoto.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(endereco_remoto.sin_zero), 8);

    if (connect(socket_local, (struct sockaddr *)&endereco_remoto, sizeof(struct sockaddr)) == -1)
		  connect_error();

    char nome[20];
    printf("Digite seu nome: ");
    scanf(" %[^\n]", nome);

    if(send(socket_local, generate_message(LOGIN, nome, log_h), MAXDATASIZE, 0) == -1)
      send_error();

    if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
      recv_error();
    buf[num_bytes] = '\0';

    if (strcmp(buf, "LOGIN_ACCEPTED") == 0){
      printf("Login aceito\n");
      while (1){
        sleep(1);
      }
    } else {
      printf("Login NEGADO\n");
      exit(0);
    }



}
