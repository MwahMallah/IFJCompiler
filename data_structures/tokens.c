#include <stdio.h>
#include "tokens.h"
#include <stdlib.h>

/********************symtable.h***********************/
/*  Předmět: IFJ - FIT VUT v Brně                    */
/*  implementace: Anastasiia Samoilova (xsamoi00)  */
/* ***************************************************/

void resize(token_list* tokens);


/*
    Creates list of tokens, sets size to 0, capacity(?) to MAX_CAPACITY, tokens to NULL. If list wasn't created returns NULL
*/
token_list* new_token_list() {
    //TODO
    
    token_list* tokens = malloc(sizeof(token_list));
    if (tokens == NULL) {
        return NULL;
    }

    tokens->size = 0;
    tokens->capacity = MAX_CAPACITY;
    tokens->tokens = NULL;

    return tokens;
}

/*
    Returns token from a given position. If there is no token returns NULL.
*/
token* token_get(token_list* tokens, int position) {
    //TODO
    
    if (tokens == NULL) {
        return NULL;
    }

    if ((position < 0) || (position >= tokens->size)) {
        return NULL;
    }

    return tokens->tokens[position];
}

/*
    Adds token with a given values to end of the token list.
*/
void token_add(token_list* tokens, enum TokenType type, char* lexeme, int* literal, int line) {  
    //TODO

    if (tokens == NULL) {
        return;
    }

    if (tokens->size == tokens->capacity) {
        resize(tokens);
    }

    token* new_token = malloc(sizeof(token));

    if (new_token == NULL) {
        return;
    }

    new_token->type = type;
    new_token->lexeme = lexeme;
    new_token->literal = literal;
    new_token->line = line;

    tokens->tokens[tokens->size] = new_token;
    tokens->size++;

    return;
}

/* resizes tokens array */
void resize(token_list* tokens) {
    tokens->capacity *= 2;
    token** garbage = tokens->tokens;
    realloc(tokens->tokens, sizeof(token*) * tokens->capacity);
    free(garbage);
}

/*
    Deallocates whole structure of tokens list.
*/
void token_delete_tokens(token_list* tokens) {
    //TODO

    if (tokens == NULL) {
        return;
    }

    for (int i = 0; i < tokens->size; i++) {
        free(tokens->tokens[i]);
    }

    free(tokens->tokens);
    free(tokens);

    return;
}
