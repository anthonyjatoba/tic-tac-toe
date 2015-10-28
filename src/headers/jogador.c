#include <string.h>
#include <stdio.h>

#include "jogador.h"

void iniciar_jogadores(){
  FILE *fp = fopen("num_jogadores", "w");
  fprintf(fp, "%d", 0);
  fclose(fp);
}

void adicionar_jogadores(){
  int num;
  FILE *fp = fopen("num_jogadores", "r");
  fscanf(fp, "%d", &num);
  fp = fopen("num_jogadores", "w");
  num++;
  fprintf(fp, "%d", num);
  fclose(fp);
}

int get_num_jogadores(){
  int num;
  FILE *fp = fopen("num_jogadores", "r");
  fscanf(fp, "%d", &num);
  fclose(fp);
  return num;
}
