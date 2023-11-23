/********************tokenTypes.h*******************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Dubrovin Maksim (xdubro01)       */
/* *********************************************** */

#ifndef __tokenTypes_h
#define __tokenTypes_h

//represents all tokens in IFJ grammar
typedef enum {
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN, TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE, TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_COLON, TOKEN_STAR, TOKEN_EOL,

    TOKEN_SLASH, TOKEN_BANG, TOKEN_BANG_EQUAL, TOKEN_EQUAL, TOKEN_EQUAL_EQUAL, TOKEN_GREATER, TOKEN_GREATER_EQUAL, TOKEN_LESS, TOKEN_LESS_EQUAL,

    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_INTEGER, TOKEN_FLOAT, TOKEN_TYPE_DOUBLE, TOKEN_TYPE_STRING, TOKEN_TYPE_INT, TOKEN_NIL,TOKEN_QUESTION, TOKEN_DOUBLE_QUESTIONS,

    TOKEN_ELSE, TOKEN_FALSE, TOKEN_FUNC, TOKEN_IF, TOKEN_RETURN, TOKEN_TRUE, TOKEN_LET, TOKEN_ARROW,
    TOKEN_VAR, TOKEN_WHILE, TOKEN_WRITE, TOKEN_EOF, TOKEN_ERROR
} TokenType;

//Klíčová slova: Double, else, func, if, Int, let, nil, return, String,
//var, while

#endif