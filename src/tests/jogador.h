#ifndef JOGADOR_H
#define JOGADOR_H

  #include <string.h>
  #include <stdio.h>

  struct jogador{
  	char nome[20];
  	int vitorias;
  };

  //Dado um nome, verifica se existe um jogador relativo a este
  int existe_jogador(char nome[20]);

  /* Cria e retorna um novo jogador*/
  struct jogador create_jogador(char nome[20]);

  /* Persiste um jogador no arquivo*/
  void persistir_jogador(struct jogador jog);

  /* Recupera um jogador a partir do seu nome*/
  struct jogador recuperar_jogador(char nome[20]);

  /* Imprime os dados de um jogador */
  void print_jogador(struct jogador jog);

#endif
