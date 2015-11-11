#ifndef MENSAGEM_H
#define MENSAGEM_H

/*
  Criei um protocolo textual com as seguintes mensagens:

  Cliente:
            START <username>: cliente solicita o início de uma partida
            MOVE <coordenada>: cliente solicita um movimento
  Servidor:
            WELCOME <char>: o servidor envia uma mensagem ao cliente com a peca que o mesmo usará
            FULL_ROOM: o jogo já tem 2 jogadores conectados
            READY <oponente>: o jogo está pronto
            VALID_MOVE: avisa ao cliente que a jogada foi validada
            OPPONENT_MOVED <coordenada>: retorna o movimento do oponente
            GAME_OVER <resultado>: o jogo acabou. O resultado pode ser WIN, LOSE ou TIE
            CONTINUE: o jogo continua
*/

  enum tipo{
    START,
    WELCOME,
    FULL_ROOM,
    READY,
    MOVE,
    VALID_MOVE,
    OPPONENT_MOVED,
    GAME_OVER,
    CONTINUE
  };

  //Cria uma string com a mensagem
  char* gerar_mensagem(int tipo_mensagem, char *valor, int print_log);

  //Retorna o tipo de uma mensagem
  enum tipo get_tipo_mensagem(char *mensagem);

  //Retorna o valor (parâmetro) de uma mensagem
  char* get_valor(char *mensagem);

#endif
