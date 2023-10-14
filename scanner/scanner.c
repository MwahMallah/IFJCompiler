/********************scanner.c***********************/
/*  Předmět: IFJ - FIT VUT v Brně                   */
/*  implementace: Anastasiia Mironova (xmiron05)    */
/* **************************************************/

#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_PROGRAM_SIZE 128

typedef struct {
    char* start;
    char* curr;
} Scanner;

Scanner scanner;

/*
    Reads through all of standard input and outputs long string of input. 
    If gets allocation error, exits with 99 code.
*/
char* readFile() {
    char* program = malloc(sizeof(char) * INITIAL_PROGRAM_SIZE); //allocates initial memory for program text
    if (program == NULL) exit(99);

    size_t size = INITIAL_PROGRAM_SIZE;
    size_t index = 0;
    int ch;

    while ((ch = getchar()) != EOF) { //iterates over all of the stdandard input
        program[index++] = ch; //stores new char at index
        if (index == size - 1) { //resizes program if needed
            size *= 2;
            char* new_program = (char*) realloc(program, size);
            if (new_program == NULL) {
                free(program);
                exit(99);
            } 
            program = new_program;
        }
    }

    program[index] = '\0';

    return program;
}

/*
    Initializes scanner, stores starting point of program in start and current char of scanner
*/
static void initScanner(char* program) {
    scanner.start = program;
    scanner.curr = program; 
}

// Returns value of current scanner char.
static char peek() {
    return scanner.curr[0];
}

/*
    Returns value of current scanner char.
    Moves current pointer by one 
*/
static char advance() {
    char ch = peek();
    scanner.curr++;
    return ch;
}

/*
    Checks if current char equals to type, returns true if equals.
*/
static bool match(char type) {
    if (peek() == type) {
        advance();
        return true;
    } 

    return false;
}

static char peekPrevios() {
    return scanner.curr[-1];
}


//Peeks at next char from current. Doesn't move current pointer.
static char peekNext() {
    return scanner.curr[1];
}

//If current points to EOF returns true.
static bool isAtEnd() {
    return peek() == '\0';
}

//Skips all white spaces, tabulations and commentaries.
static void skipWhiteSpaces() {
    while (match(' ') || match('\t') || match('/')) {
        if (peekPrevios() == '/') {
            if (match('/')) {
                while (!match('\n'));   
            } else if (match('*')) {
                while (!match('*'));
                if (!match('/')) exit(1);
            }
        }
    }
}

static Token makeFromType(TokenType type) {
    int length = (int) (scanner.curr - scanner.start);
    return makeToken(type, scanner.start, length);
}

//returns value of current scanner char
//
static Token scanToken() {
    skipWhiteSpaces();
    char ch = peek();
    
    advance();

    switch (ch)
    {
        case '*': return makeFromType(TOKEN_STAR);
        default:
            return makeFromType(TOKEN_EOF);
    }

}

static TokenList* scanTokens() {
    TokenList* list = new_token_list();

    while(!isAtEnd()) {
        Token token = scanToken();   
        token_add(list, token);
    }

    return list;    
}

TokenList* parseTokens() {
    char* program = readFile();

    initScanner(program);
    TokenList* list = scanTokens();

    return list;
}