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
#include "headers/jogador.h"
#include "headers/message.h"
#include "headers/tabuleiro.h"

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
	char buf[MAXDATASIZE], _buf[MAXDATASIZE], mensagem[MAXDATASIZE];

	char tabuleiro[] = "         ";
	char peca = 'x';
	char peca_oponente = 'o';
	int my_turn = 0;
	int end = 0;
	char nome_jogador[20];

	system("clear");
	printf("Servidor iniciado\n");

	iniciar_jogadores();
	iniciar_tabuleiro();

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
			//Tenho que fazer isso para os métodos não modificarem o buf
			strcpy(_buf, buf);

			strcpy(nome_jogador, get_value(_buf));

			if (inserir_jogador(nome_jogador) == 0){
				if (get_num_jogadores() == 1){
					my_turn = 1;
					strcpy(mensagem, generate_message(WELCOME, "x"));
				} else if (get_num_jogadores() == 2){
					peca = 'o';
					peca_oponente = 'x';
					strcpy(mensagem, generate_message(WELCOME, "o"));
				}
			} else {
				strcpy(mensagem, "FULL_ROOM");
			}

			if(send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
				send_error();

			//Aqui ele avisa aos clientes que está pronto para o jogo
			//Tá consumindo bastante cpu...
			do{
				if(send(socket_local, "WAIT", MAXDATASIZE, 0) == -1)
					send_error();
			} while(get_num_jogadores() != 2);

			if(send(socket_local, "READY", MAXDATASIZE, 0) == -1)
				send_error();

			//Aqui começa a lógica do jogo...
			do{

				//Após cada movimento, checar o status
				if (verificar_fim(tabuleiro, peca, peca_oponente) == 0){
					printf("CONTINUE\n");
					if(send(socket_local, "CONTINUE", MAXDATASIZE, 0) == -1)
						send_error();
				} else	if (verificar_fim(tabuleiro, peca, peca_oponente) == 1){
					printf("EMPATE\n");
					if(send(socket_local, "TIE", MAXDATASIZE, 0) == -1)
						send_error();
					break;
				} else if (verificar_fim(tabuleiro, peca, peca_oponente) == 2){
					printf("VITORIA\n");
					if(send(socket_local, "WIN", MAXDATASIZE, 0) == -1)
						send_error();
					break;
				} else if (verificar_fim(tabuleiro, peca, peca_oponente) == 3){
					printf("DERROTA\n");
					if(send(socket_local, "LOSE", MAXDATASIZE, 0) == -1)
						send_error();
					break;
				}

				//Vez do socket
				if (my_turn){
					//Recupero a mensagem
					if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
						recv_error();
					buf[num_bytes] = '\0';

					int coordenada = atoi(get_value(buf));
					jogada(coordenada);

					tabuleiro[coordenada-1] = peca;

					if(send(socket_local, "VALID_MOVE", MAXDATASIZE, 0) == -1)
						send_error();

					my_turn = 0;
				} else {
					//Aqui ele lê o arquivo, esperando uma atualização
					int posicao_anterior = get_posicao();
					int posicao_atual = get_posicao();

					do{
						posicao_atual = get_posicao();
						sleep(1);
					} while (posicao_anterior == posicao_atual);

					tabuleiro[posicao_atual-1] = peca_oponente;

					sprintf(mensagem, "OPPONENT_MOVED %d", posicao_atual);

					if(send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
						send_error();

					my_turn = 1;
				}
			}while(1);

		}

	}

}
