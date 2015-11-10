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
#include "headers/mensagem.h"
#include "headers/tabuleiro.h"

#define PORTA   12345
#define BACKLOG 5
#define MAXDATASIZE 100

void main(int argc, char *argv[]){
	int socket_listener, socket_local;
  struct sockaddr_in endereco_local, endereco_remoto;
  int tamanho = sizeof(struct sockaddr_in);
	char *buf, *_buf, *mensagem;
	int num_bytes;

	char tabuleiro[] = "         ";
	char peca = 'x';
	char peca_oponente = 'o';
	int my_turn = 0;
	int end = 0;
	char *nome_jogador;

	buf = (char *) calloc (MAXDATASIZE, sizeof(char));
	_buf = (char *) calloc (MAXDATASIZE, sizeof(char));
	mensagem = (char *) calloc (MAXDATASIZE, sizeof(char));
	nome_jogador = (char *) calloc (20, sizeof(char));

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
  memset(endereco_local.sin_zero,0,8);

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

			printf("Mensagem recebida: %s\n", buf);

			strcpy(_buf, buf);

			strcpy(nome_jogador, get_valor(_buf));

			if (inserir_jogador(nome_jogador) == 0){
				if (get_num_jogadores() == 1){
					my_turn = 1;
					strcpy(mensagem, gerar_mensagem(WELCOME, "x", 1));
				} else if (get_num_jogadores() == 2){
					peca = 'o';
					peca_oponente = 'x';
					strcpy(mensagem, gerar_mensagem(WELCOME, "o", 1));
				}
			} else {
				strcpy(mensagem, "FULL_ROOM");
			}

			printf("%s entrou\n", nome_jogador);

			if(send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
				send_error();

			//Aqui ele avisa aos clientes que está pronto para o jogo
			//Tá consumindo bastante cpu...
			do{
				usleep(100);
			} while(get_num_jogadores() != 2);

			if(send(socket_local, "READY", MAXDATASIZE, 0) == -1)
					send_error();
			printf("Mandei a mensagem de READY para %s\n", nome_jogador);

			//Aqui começa a lógica do jogo...
			do{
				//Após cada movimento, checar o status
				if (verificar_fim(tabuleiro, peca, peca_oponente) == 0){
					if(send(socket_local, "CONTINUE", MAXDATASIZE, 0) == -1)
						send_error();
					printf("CONTINUE\n");
				} else	if (verificar_fim(tabuleiro, peca, peca_oponente) == 1){
					if(send(socket_local, "TIE", MAXDATASIZE, 0) == -1)
						send_error();
					printf("EMPATE\n");
					break;
				} else if (verificar_fim(tabuleiro, peca, peca_oponente) == 2){
					if(send(socket_local, "WIN", MAXDATASIZE, 0) == -1)
						send_error();
					printf("VITORIA\n");
					break;
				} else if (verificar_fim(tabuleiro, peca, peca_oponente) == 3){
					if(send(socket_local, "LOSE", MAXDATASIZE, 0) == -1)
						send_error();
					printf("DERROTA\n");
					break;
				}

				//Vez do jogador
				if (my_turn){
					//Recupero a mensagem
					if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
						recv_error();
					buf[num_bytes] = '\0';

					printf("Mensagem recebida: %s\n", buf);

					int coordenada = atoi(get_valor(buf));
					jogada(coordenada);

					tabuleiro[coordenada-1] = peca;

					if(send(socket_local, gerar_mensagem(VALID_MOVE, "", 1), MAXDATASIZE, 0) == -1)
						send_error();

					my_turn = 0;
				} else {
					//Aqui ele lê o arquivo, esperando uma atualização
					int posicao_anterior = get_posicao();
					int posicao_atual = get_posicao();

					do{
						posicao_atual = get_posicao();
						usleep(1000);
					} while (posicao_anterior == posicao_atual || posicao_atual == -1);

					tabuleiro[posicao_atual-1] = peca_oponente;

					sprintf(mensagem, "OPPONENT_MOVED %d", posicao_atual);

					if(send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
						send_error();
					printf("Mensagem enviada: %s\n", mensagem);

					my_turn = 1;
				}
			} while(1);
		}
	}
}
