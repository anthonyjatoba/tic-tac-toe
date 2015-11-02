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
  int posic = -1;
  FILE *fp = fopen(PATH, "r");
  fscanf(fp, "%d", &posic);
  fclose(fp);
  return posic;
}

void imprime(char tabuleiro[10]){
  printf("   |    |   \n");
  printf(" %c | %c  | %c\n", tabuleiro[0], tabuleiro[1], tabuleiro[2]);
  printf("___|____|____\n");
  printf("   |    |   \n");
  printf(" %c | %c  | %c\n", tabuleiro[3], tabuleiro[4], tabuleiro[5]);
  printf("___|____|____\n");
  printf("   |    |   \n");
  printf(" %c | %c  | %c\n", tabuleiro[6], tabuleiro[7], tabuleiro[8]);
  printf("   |    |   \n");
}
