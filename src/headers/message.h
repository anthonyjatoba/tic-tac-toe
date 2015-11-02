#ifndef MESSAGE_H
#define MESSAGE_H

/*
  Criei um protocolo textual com as seguintes mensagens:
  Cliente:
            START <username>: cliente solicita o início de uma partida
            MOVE <coordenada>: cliente solicita um movimento
  Servidor:
            WELCOME <char>: o servidor envia uma mensagem ao cliente com o caractere que o mesmo usará
            FULL_ROOM: sala cheia

            WAIT: indica que o cliente deve esperar que outro jogador entre no jogo
            READY: o jogo está pronto (2 jogadores conectados)

            VALID_MOVE: avisa ao cliente que a jogada foi validada
            OPPONENT_MOVED <coordenada>: retorna o movimento do oponente

            WIN: cliente venceu
            LOSE: cloente perdeu
            TIE: empate
*/

  enum type{
    START,
    WELCOME,
    FULL_ROOM,
    WAIT,
    READY,
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
