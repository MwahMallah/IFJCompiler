#include <stdio.h>
#include "tokens.h"

/********************symtable.h***********************/
/*  Předmět: IFJ - FIT VUT v Brně                    */
/*  implementace: Anastasiia Samoilova (YOUR LOGIN)  */
/* ***************************************************/



/*
    Creates list of tokens, sets size to 0, capacity(?) to MAX_CAPACITY, tokens to NULL. If list wasn't created returns NULL
*/
TokenList* new_token_list() {
    //TODO
    return NULL;
}

/*
    Returns token from a given position. If there is not token returns NULL
*/
Token* token_get(TokenList* tokens, int position) {
    //TODO
    return NULL;
}

/*
    Adds token with a given values to end of the token list.
*/
void token_add(TokenList* tokens, enum TokenType type, char* lexeme, int* literal, int line) {  
    //TODO
}

/*
    Deallocates whole structure of tokens list.
*/
void token_delete_tokens(TokenList* tokens) {
    //TODO
}
