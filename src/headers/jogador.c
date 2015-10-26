#include <string.h>
#include <stdio.h>

#include "jogador.h"

int existe_jogador(char nome[20]){
	FILE *fp = fopen("jogador.rec", "r");

	struct jogador jogador_busca;

	int existe = 0;

	while(fscanf(fp, "%s\n", jogador_busca.nome) != EOF)
		if (strcmp(jogador_busca.nome, nome) == 0){
			existe = 1;
			break;
		}

	close(fp);

	return existe;
}

struct jogador create_jogador(char nome[20]){
	struct jogador novo_jogador;

	if (!existe_jogador(nome)){
		strcpy(novo_jogador.nome, nome);
		novo_jogador.vitorias = 0;
		FILE *fp = fopen("jogador.rec", "a");
		fprintf(fp, "%s\n%d\n", novo_jogador.nome, novo_jogador.vitorias);
		fclose(fp);
	} else {
		struct jogador novo = recuperar_jogador(nome);
	}

	return novo_jogador;
}

struct jogador recuperar_jogador(char nome[20]){
	FILE *fp = fopen("jogador.rec", "r");
	struct jogador jogador_recuperado;

	strcpy(jogador_recuperado.nome, "null");

	int achou = 0;

	while (fscanf(fp, "%s\n%d\n", jogador_recuperado.nome, &jogador_recuperado.vitorias) != EOF){
		if (strcmp(jogador_recuperado.nome, nome) == 0){
			achou = 1;
			break;
		}
	}

	fclose(fp);

	if (!achou){
		perror("Jogador inexistente");
	}

	return jogador_recuperado;
}

void update_jogador(struct jogador jogador_alterar){
	FILE *fp = fopen("jogador.rec", "a+");
	char nome_provisorio[20];

	printf("Nome alterar: %s\n", jogador_alterar.nome);

	while(fscanf(fp, "%s", nome_provisorio) != EOF){
		if (strcmp(nome_provisorio, jogador_alterar.nome) == 0){
			fprintf(fp, "%d\n", jogador_alterar.vitorias);
			break;
		}

	}
	fclose(fp);
}

void print_jogador(struct jogador jog){
	printf("%s\n%d\n", jog.nome, jog.vitorias);
}
