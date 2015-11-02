#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "message.h"

char* generate_message(int message_type, char *value){
  char *return_message = (char *) calloc ((strlen(value)+20), sizeof(char));

	switch(message_type){
    //START <username>
		case START:
      sprintf(return_message, "START %s", value);
			break;
    case WELCOME:
      sprintf(return_message, "WELCOME %s", value);
      break;
    case FULL_ROOM:
      sprintf(return_message, "FULL_ROOM");
      break;
    case MOVE:
      sprintf(return_message, "MOVE %s", value);
      break;
    case VALID_MOVE:
      sprintf(return_message, "VALID_MOVE");
      break;
    case OPPONENT_MOVED:
      sprintf(return_message, "OPPONENT_MOVED %s", value);
      break;
    case WIN:
      sprintf(return_message, "WIN");
      break;
    case LOSE:
      sprintf(return_message, "LOSE");
      break;
    case TIE:
      sprintf(return_message, "TIE");
      break;
	}

  printf("Mensagem gerada: %s\n", return_message);

	return return_message;
}

enum type get_message_type(char *message){
	char *tag;
	tag = strtok(message, " ");

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
	return -1;
}

char* get_value(char *message) {
   const char s[2] = " ";
   char *token;

   token = strtok(message, s);
   token = strtok(NULL, s);

   return token;
}

void log_message(char *message){
  const char s[2] = " ";
  char *token;

  token = strtok(message, s);
  printf("TAG: %s\t", token);
  token = strtok(NULL, s);
  printf("Valor: %s\n", token);

}
