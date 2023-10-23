#include <stdio.h>
#include "str.h"

int stringLength(char* string) {
    int length = 0;
    while (string[length] != '\0') length++;
    return length;
}

double strtodouble(char* lexeme) {
    double value = 0.0, decimalValue = 0.0;
    int i = 1;
    char ch = lexeme[0];
    while (ch != '.') {
        value *= 10;
        value += ch - '0';
        ch = lexeme[i++];
    }

    double divisor = 10.0;
    ch = lexeme[i++];
    do
    {
        decimalValue += (ch - '0') / divisor;
        divisor *= 10.0;
        ch = lexeme[i++];
    } while (ch != '\0');

    return value + decimalValue;
}


void addMinus(Token* token) {
    int length = stringLength(token->lexeme);
    char* newLexeme = (char*) malloc(sizeof(char) * (length + 2));
    int i = 0;
    newLexeme[0] = '-';

    while (token->lexeme[i] != '\0' ) {
        newLexeme[i + 1] = token->lexeme[i];
        i++;
    }
    
    newLexeme[i+1] = '\0';
    free(token->lexeme);
    token->lexeme = newLexeme;
}