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

#include "headers/tabuleiro.h"
#include "headers/jogador.h"

void main(int argc, char *argv[]){

    system("clear");

    int socket_local;
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

    if ((socket_local = socket(AF_INET, SOCK_STREAM, 0)) == -1){
      perror("socket");
      exit(1);
    }

    endereco_remoto.sin_family = AF_INET;
    endereco_remoto.sin_port = htons(PORTA);
    endereco_remoto.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(endereco_remoto.sin_zero), 8);

    if (get_num_jogadores() != 2){

          if (connect(socket_local, (struct sockaddr *)&endereco_remoto, sizeof(struct sockaddr)) == -1){
            perror("conect");
            exit(1);
          }

          char nome[20];
          scanf(" %[^\n]", nome);

          //envia o nome
          if (send(socket_local, nome, MAXDATASIZE, 0) == -1) {
            perror("send");
            close(socket_local);
            exit(0);
          }

          sleep(1);
          if (get_num_jogadores() == 1){
            printf("Aguarde outro jogador se conectar!\n");
            while (get_num_jogadores() == 1) {
              sleep(1);
            }
          }

          while(1)
            sleep(1);
    } else {
      printf("Ih rpz. Tá cheio\n");
    }

}
