#ifdef TABULEIRO_H
#define TABULEIRO_H

  //Reseta o arquivo de jogadores
  void iniciar_tabuleiro();
  //Salva a última jogada no arquivo
  void jogada(int posicao);

  int get_posicao();

  void imprime(char tabuleiro[10]);

  int validar_jogada(char tabuleiro[10], int posicao);
  //Verifica se o jogo acabou após o movimento

  //0 - não acabou
  //1 - empate
  //2 - vitória
  //3 - derrota
  int verificar_fim(char tabuleiro[10], char peca, char peca_oponente);

#endif
