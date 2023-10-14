/********************tokenTypes.h*******************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Dubrovin Maksim (xdubro01)       */
/* *********************************************** */

#ifndef __tokenTypes_h
#define __tokenTypes_h

//represents all tokens in IFJ grammar
typedef enum {
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN, TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE, TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_COLON, TOKEN_SLASH, TOKEN_STAR, TOKEN_NEW_LINE,

    TOKEN_BANG, TOKEN_BANG_EQUAL, TOKEN_EQUAL, TOKEN_EQUAL_EQUAL, TOKEN_GREATER, TOKEN_GREATER_EQUAL, TOKEN_LESS, TOKEN_LESS_EQUAL,

    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,

    TOKEN_AND, TOKEN_ELSE, TOKEN_FALSE, TOKEN_FUNC, TOKEN_FOR, TOKEN_IF, TOKEN_NIL, TOKEN_OR, TOKEN_PRINT, TOKEN_RETURN, TOKEN_TRUE, TOKEN_LET, 
    TOKEN_VAR, TOKEN_WHILE, TOKEN_WITH, TOKEN_EOF
} TokenType;

#endif