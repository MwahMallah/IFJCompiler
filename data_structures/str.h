#ifndef __str_h
#define __str_h

#include "../data_structures/tokens.h"
#include <stdlib.h>

double strtodouble(char* lexeme);
void addMinus(Token* token);
int compare_strings(char *str1, char *str2);
char *copy_string(char *str);


#endif