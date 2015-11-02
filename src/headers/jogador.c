#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogador.h"

#define path "jogadores.record"

void iniciar_jogadores(){
  FILE *fp = fopen(path, "w");
  fclose(fp);
}

int get_num_jogadores(){
  int num;
  char ch;

  FILE *fp = fopen(path, "r");

  while(!feof(fp)) {
    ch = fgetc(fp);
    if(ch == '\n')
      num++;
  }

  fclose(fp);

  return num;
}

//Salva um jogador no arquivo
int inserir_jogador(char* nome){
  if (get_num_jogadores() < 2){
    FILE *fp = fopen(path, "a");
    fprintf(fp, "%s\n", nome);
    fclose(fp);
    return 0;
  } else {
    return 1;
  }
}
