#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTA       12345
#define MAXDATASIZE 100

void main(int argc, char *argv[]){
    int socket_remoto;
    int num_bytes;

    char buf[MAXDATASIZE];

    struct hostent *he;

    struct sockaddr_in endereco_remoto;

    //tá feio isso aqui
    if (argc != 2){
      he = gethostbyname("localhost");
    } else {
      if ((he=gethostbyname(argv[1])) == NULL) {
        herror("gethostbyname");
        exit(1);
      }
    }

    if ((socket_remoto = socket(AF_INET, SOCK_STREAM, 0)) == -1){
      perror("socket");
      exit(1);
    }

    endereco_remoto.sin_family = AF_INET;
    endereco_remoto.sin_port = htons(PORTA);
    endereco_remoto.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(endereco_remoto.sin_zero), 8);

    if (connect(socket_remoto, (struct sockaddr *)&endereco_remoto, sizeof(struct sockaddr)) == -1){
      perror("conect");
      exit(1);
    }

    char mensagem[MAXDATASIZE];

    while(strcmp(mensagem, "sair") != 0){
      scanf(" %[^\n]", mensagem);
      if (send(socket_remoto, mensagem, MAXDATASIZE, 0) == -1)
      {
        perror("send");
        close(socket_remoto);
        exit(0);
      }
    }

    close(socket_remoto);

}
