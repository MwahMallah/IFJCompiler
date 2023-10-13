/********************tokens.h***********************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Dubrovin Maksim (xdubro01)       */
/* *********************************************** */


#ifndef __tokens_h
#define __tokens_h

#include "tokenTypes.h"

#define MAX_CAPACITY 10

typedef struct 
{
    enum TokenType type; //type of token
    char* lexeme; //string, that has literal name of token ("let", "4", "my_variable")
    int* literal; //
    int line; //used for debugging 
} Token;


//dynamic array or linked list?
typedef struct 
{
    int capacity; //?
    int size;
    token** tokens;
}TokenList;

/*
    Library API
*/
TokenList* new_token_list();
Token* token_get(token_list* tokens, int position);
void token_add(token_list* tokens, enum TokenType type, char* lexeme, int* literal, int line);
void token_delete_tokens(token_list* tokens);
/**/

#endif