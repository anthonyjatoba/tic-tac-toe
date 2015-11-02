#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabuleiro.h"

//caminho no qual o arquivo será salvo
#define PATH "tabuleiro.record"

void iniciar_tabuleiro(){
  FILE *fp = fopen(PATH, "w");
  fclose(fp);
}

void jogada(int posicao){
  FILE *fp = fopen(PATH, "w");
  fprintf(fp, "%d\n", posicao);
  fclose(fp);
}

int get_posicao(){
  int posic;
  FILE *fp = fopen(PATH, "r");
  fscanf(fp, "%d", &posic);
  fclose(fp);
  return posic;
}
