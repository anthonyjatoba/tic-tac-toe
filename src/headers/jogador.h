#ifdef ERROR_H
#define ERROR_H

  struct jogador{
    char nome[20];
  };

  void iniciar_jogadores();

  //Retorna o número de jogadores da sessão
  int get_num_jogadores(int log_h);

  //Salva um ogador no arquivo
  void inserir_jogador(char nome);

#endif
