#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ui.h"

void print_title(char *title) {
  int i;
  int text_size = strlen(title);

  for (i = 0; i < 40-text_size/2-1; i++)
    printf("_");

  printf(" %s ", title);
  if (text_size % 2 == 0)
    for (i = 40+text_size/2+1; i < 80; i++)
      printf("_");
  else
  for (i = 40+text_size/2+1; i < 79; i++)
    printf("_");
	printf("\n\n");
}

void print_menu() {
  system("clear");
  print_title("Menu");
  printf(" 1 - Novo jogo\n\n");
  printf(" 2 - Ajuda\n\n");
  printf(" 3 - Sair\n\n");
  printf(" Opção escolhida > ");
}

void print_ajuda() {
  int a;
  system("clear");
  print_title("Ajuda do jogo da velha");
  printf(" As regras são as mesmas do jogo da velha tradicional.\n\n");
  printf(" Após se conectar, escolha um nome e aguarde outro jogador logar.\n\n");
  printf(" Para fazer sua jogada, basta digitar a coordenada desejada, como no tabuleiro: \n\n");
  print_tabuleiro("123456789");
  printf("\n Digite algo e aperte enter para voltar.");
  scanf("%d", &a);
}

void print_setup(){
  system("clear");
  print_title("Novo jogo");
  printf(" Digite seu nome: ");
}

void print_tela_jogo(char tabuleiro[10], char *nome, char peca, char *oponente, char peca_oponente){
  system("clear");
  print_title("Jogo");
  printf(" %s está jogando com %c\n %s está jogando com %c\n", nome, peca, oponente, peca_oponente);
  print_tabuleiro(tabuleiro);
  printf("\n");
}

void print_tabuleiro(char tabuleiro[10]) {
  char *espacos = "                                 ";
  printf("%s    |    |   \n", espacos);
  printf("%s  %c | %c  | %c\n", espacos, tabuleiro[0], tabuleiro[1], tabuleiro[2]);
  printf("%s____|____|____\n", espacos);
  printf("%s    |    |   \n", espacos);
  printf("%s  %c | %c  | %c\n", espacos, tabuleiro[3], tabuleiro[4], tabuleiro[5]);
  printf("%s____|____|____\n", espacos);
  printf("%s    |    |   \n", espacos);
  printf("%s  %c | %c  | %c\n", espacos, tabuleiro[6], tabuleiro[7], tabuleiro[8]);
  printf("%s    |    |   \n", espacos);
}
