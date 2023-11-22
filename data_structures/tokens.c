#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include <stdlib.h>

/********************tokens.c*************************/
/*  Předmět: IFJ - FIT VUT v Brně                    */
/*  implementace: Anastasiia Samoilova (xsamoi00)    */
/* ***************************************************/


/*
    Creates list of tokens, sets size to 0, capacity to MAX_CAPACITY, tokens to NULL. If list wasn't created exits with 99 code.
*/
TokenList* new_token_list() {
    //TODO
    TokenList* tokens = malloc(sizeof(TokenList));
    if (tokens == NULL) {
        exit(99);
    }

    tokens->size = 0;
    tokens->capacity = MAX_CAPACITY;
    tokens->tokens = malloc(tokens->capacity * sizeof(Token));

    return tokens;
}

/*
    Returns token from a given position. If requested token is beyond tokens array, returns token with TOKEN_EOF type (marks the end of the token array).
*/
Token token_get(TokenList* tokens, int position) {
    //TODO
    if ((position < 0) || (position >= tokens->size)) {
        Token endToken;
        endToken.type = TOKEN_EOF;
        return endToken;
    }

    return tokens->tokens[position];
}


/* resizes tokens array */
static void resize(TokenList* tokens) {
    tokens->capacity *= 2;
    Token* garbage = tokens->tokens;

    Token* new_tokens = realloc(tokens->tokens, sizeof(Token) * tokens->capacity);
    if (new_tokens == NULL) {
        free(tokens->tokens);
        exit(99);
    }

    tokens->tokens = new_tokens;    
}

/*
    Adds token with a given values to end of the token list.
*/
void token_add(TokenList* tokens, Token new_token) {  
    //TODO
    if (tokens == NULL) {
        return;
    }

    if (tokens->size == tokens->capacity) {
        resize(tokens);
    }

    tokens->tokens[tokens->size] = new_token;
    (tokens->size)++;

    return;
}

/*
    Deallocates whole structure of tokens list.
*/
void token_delete_tokens(TokenList* list) {
    if (list == NULL) return;

    for (int i = 0; i < list->size; i++) {
        free(list->tokens[i].lexeme);    
    }

    free(list->tokens);
    free(list);

    return;
}

// Returns new token
Token makeToken(TokenType type, char* lexeme) {
    Token tok; 
    tok.type = type;
    tok.lexeme = lexeme;

    return tok;
}

