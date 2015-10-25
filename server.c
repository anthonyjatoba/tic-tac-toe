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

void main(){
  /* Declaração de variáveis */

  int socket_local, socket_remoto;
  //sockaddr_in referente ao servidor
  struct sockaddr_in endereco_local;
  //sockaddr_in referente ao cliente
  //TODO: acho que vou precisar de dois desses
  struct sockaddr_in endereco_remoto;
  //guarda o tamanho para o accept
  int tamanho = sizeof(struct sockaddr_in);

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

    //para verificação
    printf("Conectado a %s\n", inet_ntoa(endereco_remoto.sin_addr));

  }

}
