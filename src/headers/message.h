#ifndef MESSAGE_H
#define MESSAGE_H

  enum type{
    LOGIN,
    LOGIN_ACCEPTED,
    LOGIN_DENYED
  };

  char* generate_message(int message_type, char *value, int log_h);

  int get_message_type(char *value, int log_h);

  char* get_value(char* message, int log_h);

#endif
