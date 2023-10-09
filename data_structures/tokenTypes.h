/********************tokenTypes.h*******************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Dubrovin Maksim (xdubro01)       */
/* *********************************************** */

#ifndef __tokenTypes_h
#define __tokenTypes_h

//represents all tokens in IFJ grammar
enum TokenType {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS,
    COLON, SLASH, STAR,

    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    AND, ELSE, FALSE, FUNC, FOR, IF, NIL, OR, PRINT, RETURN, TRUE, LET, WHILE, ENDFILE
};

#endif