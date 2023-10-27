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


int compare_strings(char *str1, char *str2){
    while(*str1 && *str2){
        if(*str1 != *str2) return 0;
        str1++;
        str2++;
    }
    if(*str1 == '\0' && *str2 == '\0'){
        return 1;
    }
    return 0;
}//todo is public?


/*
 * Creates pointer to block of allocated memory
 * which contains copy of str string
 */
char *copy_string(char *str){
    int length = 0;
    while(str[length] != '\0'){
        length++;
    }
    char *newStr = malloc(sizeof(char) * (length + 1));
    for(int i = 0; i < length; ++i){
        newStr[i] = str[i];
    }
    newStr[length] = '\0';
    return newStr;
}