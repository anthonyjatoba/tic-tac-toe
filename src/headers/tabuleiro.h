#ifdef TABULEIRO_H
#define TABULEIRO_H

  //Reseta o arquivo de jogadores
  void iniciar_tabuleiro();
  //Salva a última jogada no arquivo
  void jogada(int posicao);

  int get_posicao();

  void imprime(char tabuleiro[10]);

  int validar_jogada(char tabuleiro[10], int posicao);

#endif
