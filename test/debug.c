/********************debug.c*************************/
/*  Předmět: IFJ - FIT VUT v Brně                   */
/*  implementace: Dubrovin Maksim (xdubro01)        */
/* **************************************************/

#include <stdio.h>
#include "debug.h"

void printType(ValueType type) {
    switch (type)
    {
        case INTEGER:
            printf("INTEGER\n");
            break;
        case STRING:
            printf("STRING\n");
            break;
        case FLOAT:
            printf("FLOAT\n");
            break;
        case BOOLEAN:
            printf("BOOLEAN\n");
            break;
        case NONE_TYPE:
            printf("NONE_TYPE\n");
            break;  
        default:
            printf("UNKNOWN TYPE\n");
            break;
    }
}

char* getType(TokenType type) {
    char* string;
    switch (type)
    {
        case TOKEN_ARROW:
            string = "TOKEN_ARROW";
            break;
        case TOKEN_LEFT_PAREN:
            string = "TOKEN_LEFT_PAREN";
            break;
        case TOKEN_RIGHT_PAREN:
            string = "TOKEN_RIGHT_PAREN";
            break;
        case TOKEN_LEFT_BRACE:
            string = "TOKEN_LEFT_BRACE";
            break;
        case TOKEN_RIGHT_BRACE:
            string = "TOKEN_RIGHT_BRACE";
            break;
        case TOKEN_COMMA:
            string = "TOKEN_COMMA";
            break;
        case TOKEN_DOT:
            string = "TOKEN_DOT";
            break;
        case TOKEN_MINUS:
            string = "TOKEN_MINUS";
            break;
        case TOKEN_PLUS:
            string = "TOKEN_PLUS";
            break;
        case TOKEN_COLON:
            string = "TOKEN_COLON";
            break;
        case TOKEN_SLASH:
                    string = "TOKEN_SLASH";
                    break;
        case TOKEN_STAR:
                    string = "TOKEN_STAR";
                    break;   
        case TOKEN_EOL:
                    string = "TOKEN_EOL";
                    break; 
        case TOKEN_BANG:
                    string = "TOKEN_BANG";
                    break;
        case TOKEN_BANG_EQUAL:
                    string = "TOKEN_BANG_EQUAL";
                    break;
        case TOKEN_EQUAL:
                    string = "TOKEN_EQUAL";
                    break;
        case TOKEN_EQUAL_EQUAL:
                    string = "TOKEN_EQUAL_EQUAL";
                    break;
        case TOKEN_GREATER:
                    string = "TOKEN_GREATER";
                    break;
        case TOKEN_GREATER_EQUAL:
                    string = "TOKEN_GREATER_EQUAL";
                    break;
        case TOKEN_LESS:
                    string = "TOKEN_LESS";
                    break;
        case TOKEN_LESS_EQUAL:
                    string = "TOKEN_LESS_EQUAL";
                    break;
        case TOKEN_IDENTIFIER:
                    string = "TOKEN_IDENTIFIER";
                    break;
        case TOKEN_STRING:
                    string = "TOKEN_STRING";
                    break;
        case TOKEN_INTEGER:
                    string = "TOKEN_INTEGER";
                    break;
        case TOKEN_FLOAT:
                    string = "TOKEN_FLOAT";
                    break;
        case TOKEN_QUESTION:
                    string = "TOKEN_QUESTION";
                    break;
        case TOKEN_DOUBLE_QUESTIONS:
                    string = "TOKEN_DOUBLE_QUESTIONS";
                    break;
        case TOKEN_ELSE:
                    string = "TOKEN_ELSE";
                    break;
        case TOKEN_FALSE:
                    string = "TOKEN_FALSE";
                    break;
        case TOKEN_FUNC:
                    string = "TOKEN_FUNC";
                    break;
        case TOKEN_IF:
                    string = "TOKEN_IF";
                    break;
        case TOKEN_NIL:
                    string = "TOKEN_NIL";
                    break;
        case TOKEN_TYPE_INT:
                    string = "TOKEN_TYPE_INT";
                    break;
        case TOKEN_TYPE_DOUBLE:
                    string = "TOKEN_TYPE_DOUBLE";
                    break;
        case TOKEN_TYPE_STRING:
                    string = "TOKEN_TYPE_STRING";
                    break;
        case TOKEN_RETURN:
                    string = "TOKEN_RETURN";
                    break;
        case TOKEN_TRUE:
                    string = "TOKEN_TRUE";
                    break;
        case TOKEN_LET:
                    string = "TOKEN_LET";
                    break;
        case TOKEN_VAR:
                    string = "TOKEN_VAR";
                    break;
        case TOKEN_WHILE:
                    string = "TOKEN_WHILE";
                    break;
        case TOKEN_WRITE:
            string = "TOKEN_WRITE";
            break;
        case TOKEN_EOF:
                    string = "TOKEN_EOF";
                    break;
        default:
            break;
    }

    return string;
}

void printToken(Token token) {
    char* type = getType(token.type);
    if (token.type == TOKEN_EOF || token.type == TOKEN_EOL) {
        printf("%s\n", type);
    } else {
        printf("%s, '%s'\n", type, token.lexeme);
    }
}