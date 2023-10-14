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
char* readInput() {
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

//If current points to EOF returns true.
static bool isAtEnd() {
    return peek() == '\0';
}

//Peeks at next char from current. Doesn't move current pointer.
static char peekNext() {
    if (isAtEnd()) return '\0';
    return scanner.curr[1];
}


//Skips all white spaces, tabulations and commentaries.
static void skipWhiteSpaces() {
    // while (match(' ') || match('\t') || match('/')) {
    //     if (peekPrevios() == '/') {
    //         if (match('/')) {
    //             while (!match('\n')) advance();   
    //         } else if (match('*')) {
    //             while (!match('*')) advance();
    //             if (!match('/')) exit(1);
    //         }
    //     }
    // }

    for(;;) { // infinite loop
        char ch = peek();
        switch (ch)
        {
            case ' ':
            case '\t':        
            case '\r':
                advance();
                break;            
            case '/':
                if (peekNext() == '/') {
                    while(peek() != '\n' && !isAtEnd()) {advance();}
                    advance(); //skip newline after comment end
                } else if (peekNext() == '*') {
                    while (peek() != '*' && peekNext() != '/' && !isAtEnd()) {advance();}                    
                }
            default:
                return;
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
    scanner.start = scanner.curr;

    if (isAtEnd()) return makeFromType(TOKEN_EOF);

    char ch = advance();

    switch (ch)
    {
        case '*': return makeFromType(TOKEN_STAR);
        case '+': return makeFromType(TOKEN_PLUS);
        case '-': return makeFromType(TOKEN_MINUS);
        case '(': return makeFromType(TOKEN_LEFT_PAREN);
        case ')': return makeFromType(TOKEN_RIGHT_PAREN);
        case '{': return makeFromType(TOKEN_LEFT_BRACE);
        case '}': return makeFromType(TOKEN_RIGHT_BRACE);
        case '/': return makeFromType(TOKEN_SLASH);
        case ',': return makeFromType(TOKEN_COMMA);
        case '.': return makeFromType(TOKEN_DOT);
        case ':': return makeFromType(TOKEN_COLON);
        case '\n': return makeFromType(TOKEN_NEW_LINE);
        case '!':
            return match('=')? makeFromType(TOKEN_BANG_EQUAL):makeFromType(TOKEN_BANG);
        case '=':
            return match('=')? makeFromType(TOKEN_EQUAL_EQUAL): makeFromType(TOKEN_EQUAL);
        case '<':
            return match('=')? makeFromType(TOKEN_LESS_EQUAL) : makeFromType(TOKEN_LESS);
        case '>':
            return match('=')? makeFromType(TOKEN_GREATER_EQUAL) : makeFromType(TOKEN_GREATER);
    }

}

//Scances for tokens from the entire content of a program and constructs a list of tokens.
TokenList* scanTokens(char* program) {
    initScanner(program);

    TokenList* list = new_token_list();
    bool atEnd = false;

    while(!atEnd) {
        Token token = scanToken();   
        token_add(list, token);
        if (token.type == TOKEN_EOF) atEnd = true;
    }

    return list;    
}