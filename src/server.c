#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#include "headers/error.h"
#include "headers/message.h"
#include "headers/jogador.h"

#define PORTA   12345
#define BACKLOG 5
#define MAXDATASIZE 100

void main(int argc, char *argv[]){
	int socket_listener, socket_local;
  //sockaddr_in referente ao servidor
  struct sockaddr_in endereco_local, endereco_remoto;
  //guarda o tamanho para o accept
  int tamanho = sizeof(struct sockaddr_in);
  int num_bytes;
	char buf[MAXDATASIZE];
	char mensagem[MAXDATASIZE];
	int log_h = 0;

	iniciar_jogadores();

	if (argc == 2 && strcmp(argv[1], "log") == 0)
		log_h = 1;

	printf("Servidor iniciado");
	if (log_h)
		printf(" com log habilitado");
	printf("\n");

  /* Inicio o socket*/
  socket_listener = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuro o endereco_local */
  endereco_local.sin_family = AF_INET;
  endereco_local.sin_port = htons(PORTA);
  endereco_local.sin_addr.s_addr = INADDR_ANY;  //Automático
  bzero(&(endereco_local.sin_zero),8);

  /* bind */
  if (bind(socket_listener, (struct sockaddr *)&endereco_local, sizeof(struct sockaddr)) == -1)
	bind_error();

  /* listen */
  if (listen(socket_listener, BACKLOG) < 0)
	listen_error();

  /* aqui acontece a mágica */
  while(1){
    /* accept */
    if ((socket_local = accept(socket_listener, (struct sockaddr *)&endereco_remoto, &tamanho)) < 0){
      perror("accept");
      //caso a conexão não seja aceita (dispara erro), o programa volta ao inicio da repetição
      continue;
    }

    //para verificação
    printf("Conectado a %s\n", inet_ntoa(endereco_remoto.sin_addr));

		if (!fork()){

			if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
			  recv_error();

			buf[num_bytes] = '\0';

			strcpy(mensagem, buf);

			printf("%s\n", mensagem);
			get_message_type(mensagem, log_h);

			strcpy(mensagem, buf);
			if (inserir_jogador(get_value(mensagem, log_h), log_h) == 0){
				if(send(socket_local, generate_message(LOGIN_ACCEPTED, "", log_h), MAXDATASIZE, 0) == -1)
					send_error();
			} else {
				if(send(socket_local, generate_message(LOGIN_DENYED, "", log_h), MAXDATASIZE, 0) == -1)
					send_error();
			}

		}

	}
}
