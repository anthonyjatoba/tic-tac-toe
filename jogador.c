#include <string.h>
#include <stdio.h>

struct jogador{
	char nome[20];
	int vitorias;
};

struct jogador criar_jogador(char nome[20]){
	struct jogador jogador_criado;

	strcpy(jogador_criado.nome, nome);
	jogador_criado.vitorias = 0;

	return jogador_criado;
}

void persistir_jogador(struct jogador jog){
	FILE *file_pointer = fopen("jogador.record", "a");
	fprintf(file_pointer, "%s\t%d\n", jog.nome, jog.vitorias);
	fclose(file_pointer);
}

struct jogador recuperar_jogador(char nome[20]){
	FILE *file_pointer = fopen("jogador.record", "r");
	struct jogador jog;

	int achou = 1;

	while(fscanf(file_pointer, "%s\t%d\n", jog.nome, &jog.vitorias) != EOF	){
		if (strcmp(jog.nome, nome) == 0){
			achou = 0;
			break;
		}
	}

	if (achou){
			jog = criar_jogador(nome);
			persistir_jogador(jog);
	}

	return jog;
}

void print_jogador(struct jogador jog){
	printf("%s\t%d\n", jog.nome, jog.vitorias);
}
