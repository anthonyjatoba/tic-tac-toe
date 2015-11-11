#ifdef ERROR_H
#define ERROR_H

  struct jogador{
    char nome[20];
  };

  //Reseta o arquivo de jogadores
  void iniciar_jogadores();

  //Retorna o número de jogadores da sessão
  int get_num_jogadores();

  //Salva um jogador no arquivo
  void inserir_jogador(char nome);

  char* get_nome_oponente(char *nome_jogador);

#endif
