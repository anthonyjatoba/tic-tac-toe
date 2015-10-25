#ifndef JOGADOR_H
#define JOGADOR_H

  #include <string.h>
  #include <stdio.h>

  struct jogador;

  /* Cria e retorna um novo jogador*/
  struct jogador criar_jogador(char nome[20]);

  /* Persiste um jogador no arquivo*/
  void persistir_jogador(struct jogador jog);

  /* Recupera um jogador a partir do seu nome*/
  struct jogador recuperar_jogador(char nome[20]);

  /* Imprime os dados de um jogador */
  void print_jogador(struct jogador jog);

#endif
