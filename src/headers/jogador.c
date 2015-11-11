#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogador.h"

//caminho no qual o arquivo será salvo
#define DIRETORIO "jogadores.record"

void iniciar_jogadores() {
  FILE *fp = fopen(DIRETORIO, "w");
  fclose(fp);
}

int get_num_jogadores() {
  char ch;
  int num = 0;
  FILE *fp = fopen(DIRETORIO, "r");

  while(!feof(fp)) {
    ch = fgetc(fp);
    if(ch == '\n')
      num++;
  }

  fclose(fp);
  return num;
}

//Salva um jogador no arquivo. Retorna 1 caso não possa inserir
int inserir_jogador(char* nome) {
  if (get_num_jogadores() < 2) {
    FILE *fp = fopen(DIRETORIO, "a");
    fprintf(fp, "%s\n", nome);
    fclose(fp);
    return 0;
  }
  return 1;
}

void get_nome_oponente(char *nome_jogador, char*nome_oponente){
  char *nome;
  nome = (char *) calloc (20, sizeof(char));

  FILE *fp = fopen(DIRETORIO, "r");
  fscanf(fp, "%s\n",  nome);
  if (strcmp(nome, nome_jogador) == 0)
    fscanf(fp, "%s\n", nome);

  strcpy(nome_oponente, nome);

  fclose(fp);
}
