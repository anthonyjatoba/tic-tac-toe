#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogador.h"

//caminho no qual o arquivo será salvo
#define PATH "jogadores.record"

void iniciar_jogadores() {
  FILE *fp = fopen(PATH, "w");
  fclose(fp);
}

int get_num_jogadores() {
  char ch;
  int num = 0;
  FILE *fp = fopen(PATH, "r");

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
    FILE *fp = fopen(PATH, "a");
    fprintf(fp, "%s\n", nome);
    fclose(fp);
    return 0;
  }
  return 1;
}
