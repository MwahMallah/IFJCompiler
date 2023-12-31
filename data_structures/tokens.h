/********************tokens.h***********************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Dubrovin Maksim (xdubro01)       */
/* *********************************************** */


#ifndef __tokens_h
#define __tokens_h

#include "tokenTypes.h"

#define MAX_CAPACITY 8

typedef struct 
{
    TokenType type; //type of token
    char* lexeme; //lexeme stored in token
} Token;


//Token list made from dynamic array
typedef struct 
{
    int capacity; 
    int size;
    Token* tokens;
}TokenList;

/*
    Library API
*/
TokenList* new_token_list();
Token token_get(TokenList* tokens, int position);
void token_add(TokenList* tokens, Token token);
void token_delete_tokens(TokenList* tokens);
Token makeToken(TokenType type, char* lexeme);
/**/

#endif