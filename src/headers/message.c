
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"

char* generate_message(int message_type, char *value, int log_h);

int get_message_type(char *value, int log_h);

char* get_value(char* message);
