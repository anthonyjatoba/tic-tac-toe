#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "message.h"

char* generate_message(int message_type, char *value, int log_h){
  char *return_message;

	return_message = (char *) calloc ((strlen(value)+20),sizeof(char));

	switch(message_type){
		case LOGIN:{
      sprintf(return_message, "LOGIN %s", value);
			break;
		}
    case LOGIN_ACCEPTED:{
      sprintf(return_message, "LOGIN_ACCEPTED");
      break;
    }
    case LOGIN_DENYED:{
      sprintf(return_message, "LOGIN_DENYED");
      break;
    }
	}

	if(log_h){
		printf("Mensagem gerada: %s\n", return_message);
		fflush(stdout);
	}

	return return_message;
}

int get_message_type(char *message, int log_h){

	char *tag;
	tag = strtok(message, " ");

  if(log_h)
    printf("Tipo da mensagem: %s\n", tag);

	if(strcmp(tag, "LOGIN") == 0)
		return LOGIN;
  if(strcmp(tag, "LOGIN_ACCEPTED") == 0)
  		return LOGIN_ACCEPTED;
  if(strcmp(tag, "LOGIN_DENYED") == 0)
  		return LOGIN_DENYED;

	return -1;
}

char* get_value(char *message, int log_h) {
   const char s[2] = " ";
   char *token;

   token = strtok(message, s);
   token = strtok(NULL, s);

   if (log_h)
    printf("Valor da mensagem: %s\n", token);

   return token;
}
