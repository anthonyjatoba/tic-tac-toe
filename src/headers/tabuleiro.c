#include <string.h>
#include <stdio.h>

#include "tabuleiro.h"

void iniciar_tabuleiro(char tabuleiro[3][3]){
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      tabuleiro[i][j] = '#';
}

void salvar_tabuleiro(char tabuleiro[3][3]){
  int i, j;
  FILE *fp = fopen("tabuleiro", "w");
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      fprintf(fp, "%c", tabuleiro[i][j]);
  fclose(fp);
}

void recuperar_tabuleiro(char tabuleiro[3][3]){
  int i, j;
  FILE *fp = fopen("tabuleiro", "r");
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      fscanf(fp, "%c", &tabuleiro[i][j]);
  fclose(fp);
}

void imprimir_tabuleiro(char tabuleiro[3][3]){
  printf(" %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
  printf("___|___|___\n");
  printf(" %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
  printf("___|___|___\n");
  printf(" %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}
