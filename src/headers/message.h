#ifndef MESSAGE_H
#define MESSAGE_H

/*
  Cliente:
            START <username>: cliente solicita o início de uma partida
            MOVE <coordenada>: cliente solicita um movimento
  Servidor:
            WELCOME <char>: o servidor envia uma mensagem ao cliente com o caractere que o mesmo usará
            FULL_ROOM: sala cheia
            VALID_MOVE: avisa ao cliente que a jogada foi válida
            OPPONENT_MOVED <coordenada>: retorna o movimento do oponente
            WIN:
            LOSE:
            TIE:
*/

  enum type{
    START,
    WELCOME,
    FULL_ROOM,
    MOVE,
    VALID_MOVE,
    OPPONENT_MOVED,
    WIN,
    LOSE,
    TIE
  };

  char* generate_message(int message_type, char *value);

  enum type get_message_type(char *value);

  char* get_value(char* message);

  void log_message(char *message);

#endif
