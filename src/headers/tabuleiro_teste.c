#include<stdio.h>
#include<stdlib.h>

#include "tabuleiro.h"

int main(int argc, char const *argv[]) {
  char tabuleiro[3][3];
  int i, j;

  iniciar_tabuleiro(tabuleiro);

  salvar_tabuleiro(tabuleiro);

  recuperar_tabuleiro(tabuleiro);

  imprimir_tabuleiro(tabuleiro);
}
