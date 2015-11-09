#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabuleiro.h"

//caminho no qual o arquivo será salvo
#define PATH "tabuleiro.record"
#define NAO_ACABOU 0
#define EMPATE 1
#define VITORIA 2
#define DERROTA 3

void iniciar_tabuleiro() {
  FILE *fp = fopen(PATH, "w");
  fclose(fp);
}

void jogada(int posicao) {
  FILE *fp = fopen(PATH, "w");
  fprintf(fp, "%d\n", posicao);
  fclose(fp);
}

int get_posicao() {
  int posic = -1;
  FILE *fp = fopen(PATH, "r");
  fscanf(fp, "%d", &posic);
  fclose(fp);
  return posic;
}

void imprime(char tabuleiro[10]){
  printf("    |    |   \n");
  printf("  %c | %c  | %c\n", tabuleiro[0], tabuleiro[1], tabuleiro[2]);
  printf("____|____|____\n");
  printf("    |    |   \n");
  printf("  %c | %c  | %c\n", tabuleiro[3], tabuleiro[4], tabuleiro[5]);
  printf("____|____|____\n");
  printf("    |    |   \n");
  printf("  %c | %c  | %c\n", tabuleiro[6], tabuleiro[7], tabuleiro[8]);
  printf("    |    |   \n");
}

int validar_jogada(char tabuleiro[10], int posicao) {
  if (posicao >= 1 && posicao <= 9)
    if (tabuleiro[posicao-1] == ' ')
      return 1;
  return 0;
}

int verificar_fim(char *tabuleiro, char peca, char peca_oponente){
  if (tabuleiro[0] == peca && tabuleiro[1] == peca && tabuleiro[2] == peca)
    return VITORIA;
  if (tabuleiro[3] == peca && tabuleiro[4] == peca && tabuleiro[5] == peca)
    return VITORIA;
  if (tabuleiro[6] == peca && tabuleiro[7] == peca && tabuleiro[8] == peca)
    return VITORIA;
  if (tabuleiro[0] == peca && tabuleiro[3] == peca && tabuleiro[6] == peca)
    return VITORIA;
  if (tabuleiro[1] == peca && tabuleiro[4] == peca && tabuleiro[7] == peca)
    return VITORIA;
  if (tabuleiro[2] == peca && tabuleiro[5] == peca && tabuleiro[8] == peca)
    return VITORIA;
  if (tabuleiro[0] == peca && tabuleiro[4] == peca && tabuleiro[8] == peca)
    return VITORIA;
  if (tabuleiro[2] == peca && tabuleiro[4] == peca && tabuleiro[6] == peca)
    return VITORIA;

  if (tabuleiro[0] == peca_oponente && tabuleiro[1] == peca_oponente && tabuleiro[2] == peca_oponente)
    return DERROTA;
  if (tabuleiro[3] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[5] == peca_oponente)
    return DERROTA;
  if (tabuleiro[6] == peca_oponente && tabuleiro[7] == peca_oponente && tabuleiro[8] == peca_oponente)
    return DERROTA;
  if (tabuleiro[0] == peca_oponente && tabuleiro[3] == peca_oponente && tabuleiro[6] == peca_oponente)
    return DERROTA;
  if (tabuleiro[1] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[7] == peca_oponente)
    return DERROTA;
  if (tabuleiro[2] == peca_oponente && tabuleiro[5] == peca_oponente && tabuleiro[8] == peca_oponente)
    return DERROTA;
  if (tabuleiro[0] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[8] == peca_oponente)
    return DERROTA;
  if (tabuleiro[2] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[6] == peca_oponente)
    return DERROTA;

  int i;
  for (i = 0; i < 9; i++)
    if (tabuleiro[i] == ' ')
      return NAO_ACABOU;

  return EMPATE;

}
