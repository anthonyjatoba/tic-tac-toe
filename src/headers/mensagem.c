#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mensagem.h"

char* gerar_mensagem(int tipo_mensagem, char *valor, int print_log){
  char *mensagem = (char *) calloc ((strlen(valor)+20), sizeof(char));

	switch(tipo_mensagem){
    //START <username>
		case START:
      sprintf(mensagem, "START %s", valor);
			break;
    case WELCOME:
      sprintf(mensagem, "WELCOME %s", valor);
      break;
    case FULL_ROOM:
      sprintf(mensagem, "FULL_ROOM");
      break;
    case MOVE:
      sprintf(mensagem, "MOVE %s", valor);
      break;
    case VALID_MOVE:
      sprintf(mensagem, "VALID_MOVE");
      break;
    case OPPONENT_MOVED:
      sprintf(mensagem, "OPPONENT_MOVED %s", valor);
      break;
    case WIN:
      sprintf(mensagem, "WIN");
      break;
    case LOSE:
      sprintf(mensagem, "LOSE");
      break;
    case TIE:
      sprintf(mensagem, "TIE");
      break;
    case CONTINUE:
        sprintf(mensagem, "CONTINUE");
        break;
	}

  if (print_log)
    printf("Mensagem gerada: %s\n", mensagem);

	return mensagem;
}

enum tipo get_tipo_mensagem(char *mensagem){
  char *_mensagem = (char *) calloc ((strlen(mensagem)), sizeof(char));
  strcpy(_mensagem, mensagem);
	char *tag;
	tag = strtok(_mensagem, " ");

	if(strcmp(tag, "START") == 0)
    return START;
  if(strcmp(tag, "WELCOME") == 0)
  		return WELCOME;
  if(strcmp(tag, "MOVE") == 0)
  		return MOVE;
  if(strcmp(tag, "VALID_MOVE") == 0)
  		return VALID_MOVE;
  if(strcmp(tag, "OPPONENT_MOVED") == 0)
  		return OPPONENT_MOVED;
  if(strcmp(tag, "WIN") == 0)
  		return WIN;
  if(strcmp(tag, "LOSE") == 0)
      return LOSE;
  if(strcmp(tag, "TIE") == 0)
      return TIE;
  if(strcmp(tag, "CONTINUE") == 0)
      return CONTINUE;
	return -1;
}

char* get_valor(char *mensagem) {
  char *_mensagem = (char *) calloc ((strlen(mensagem)), sizeof(char));
  strcpy(_mensagem, mensagem);
  const char s[2] = " ";
  char *token;

  token = strtok(_mensagem, s);
  token = strtok(NULL, s);

  return token;
}
