#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define PORTA   12345
#define BACKLOG 10
#define MAXDATASIZE 100

void main(){
  int socket_local, socket_remoto;
  //Struct contendo informações de endereço do servidor e cliente
  struct sockaddr_in endereco_local, endereco_remoto;
  //guarda o tamanho para o accept
  int tamanho = sizeof(struct sockaddr_in);

  char buf[MAXDATASIZE];
  int num_bytes;

  /* Inicio o socket*/
  socket_local = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuro o endereco_local */
  endereco_local.sin_family = AF_INET;
  endereco_local.sin_port = htons(PORTA);
  endereco_local.sin_addr.s_addr = INADDR_ANY;  //Automático
  bzero(&(endereco_local.sin_zero),8);

  /* bind */
  if (bind(socket_local, (struct sockaddr *)&endereco_local, sizeof(struct sockaddr)) == -1){
    perror("bind");
    exit(1);
  }

  /* listen */
  if (listen(socket_local, BACKLOG) < 0){
    perror("listen");
    exit(1);
  }

  /* aqui acontece a mágica */
  while(1){
    /* accept */
    if ((socket_remoto = accept(socket_local, (struct sockaddr *)&endereco_remoto, &tamanho)) < 0){
      perror("accept");
      //caso a conexão não seja aceita (dispara erro), o programa volta ao inicio da repetição
      continue;
    }

    printf("Conectado a %s\n", inet_ntoa(endereco_remoto.sin_addr));

      if (!fork()) {
        do{
          if ((num_bytes = recv(socket_remoto, buf, MAXDATASIZE, 0)) == -1) {
            perror("recv");
            exit(1);
          }
          buf[num_bytes] = '\0';
          printf("Recebido: %s\n", buf);
        } while(strcmp(buf, "sair") != 0);

        close(socket_remoto);
      }

    }


}
