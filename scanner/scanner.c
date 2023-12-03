/********************scanner.c***********************/
/*  Předmět: IFJ - FIT VUT v Brně                   */
/*  implementace: Anastasiia Mironova (xmiron05)    */
/* **************************************************/

#include "../data_structures/str.h"
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../test/debug.h"


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

//finds length of resulting string. For characters, with ascii code equal to 
//0-32, 35 and 92 length of one char is 4
static int findStringLength() {
    char* strPtr = scanner.start;

    int length = 0;
    while (strPtr != scanner.curr){
        length++;
        if ((strPtr[0] >= 0 && strPtr[0] <= 32) || (strPtr[0] == 35) || (strPtr[0] == 92)) length += 3;
        strPtr++;
    }
    return length;
}

static bool addChar(char* string, char ch1, char ch2, int* pos, bool isLong) {
    if (ch1 == '\\') {
        int value;
        switch (ch2)
        {
            case 'n':
                value = 10;
                break;
            case 'r':
                value = 13;
                break;
            case 't':
                value = 9;
                break;            
            case '\\':
                value = 92;
                break;
            case '"':
                value = 34;
                break;
            default:
                *pos = -1;
                return false;
        }
        sprintf(string + *pos, "\\%03d", value);
        (*pos) += 4;
        return true;
    } else if ((ch1 <= 32 && ch1 >= 0) || (ch1 == 35) || (ch1 == 92)) {
        if (!isLong && ch1 != 32) {
            *pos = -1;
            return false;
        }
        sprintf(string + *pos, "\\%03d", (int)ch1);
        (*pos) += 4;
    } else {
        string[*pos] = ch1;
        (*pos)++;
    }

    return false;
}


//Skips all white spaces, tabulations and commentaries.
static TokenType skipWhiteSpaces() {
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
                    advance(); //skip newline after comment's end
                    skipWhiteSpaces();
                } else if (peekNext() == '*') {
                    int inner = 0;
                    char ch1, ch2;
                    ch1 = advance();
                    do {
                        if (isAtEnd()) return TOKEN_ERROR;
                        ch2 = advance();
                        if (ch1 == '*' && ch2 == '/') inner--;
                        else if (ch1 == '/' && ch2 == '*') inner++;
                        ch1 = ch2;                        
                    } while(inner != 0);
                    skipWhiteSpaces();         
                }
            default:
                return TOKEN_ARROW;
        }
    }
    return TOKEN_ARROW;
}

//Makes token from a given type
static Token makeFromType(TokenType type) {
    char* lexeme;
    int i = 0;
    char ch1, ch2;
    int length = (int) (scanner.curr - scanner.start); 

    if (type == TOKEN_LONG_STRING || type == TOKEN_STRING) {
        bool escapeChar = false;
        int stringLength = findStringLength();
        lexeme = malloc(sizeof(char) * (stringLength + 1));
        int escapeQuotesLength = type == TOKEN_LONG_STRING? 3 : 1;
        int startPos = type == TOKEN_LONG_STRING? 5 : 1;

        for (int pos = startPos; pos < length - escapeQuotesLength; pos++) { //starts from 1 to escape '"'
            ch1 = scanner.start[pos];
            ch2 = scanner.start[pos + 1];
            escapeChar = addChar(lexeme, ch1, ch2, &i, type == TOKEN_LONG_STRING);
            if (i == - 1) {
                return makeFromType(TOKEN_ERROR);
            }
            if (escapeChar) pos++;
        }
        lexeme[i] = '\0';
        return makeToken(TOKEN_STRING, lexeme);
    } else {
        lexeme = malloc(sizeof(char) * (length + 1)); //allocates space for needed lexeme
        for (i; i < length; i++) {
            lexeme[i] = scanner.start[i]; //populates lexeme with chars from give input
        }    
    }
    lexeme[i] = '\0';
    return makeToken(type, lexeme);
}


static bool isNumber(char ch) {
    return ch >= '0' && ch <= '9';
}

static bool isAlpha() {
    char ch = scanner.curr[0];
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == '_');
}

static Token number() {
    while (isNumber(peek())) advance();

    if (peek() == '.' && isNumber(peekNext())) {
        advance();
        while (isNumber(peek())) advance();
        return makeFromType(TOKEN_FLOAT);
    }
    return makeFromType(TOKEN_INTEGER);
}

static Token string() {
    while (peek() != '"' && !isAtEnd()){
        if (peek() == '\\' && peekNext() == '"') advance();
        advance();
    } 
    advance();
    return makeFromType(TOKEN_STRING);
}

static Token longString() {
    while (peek() != '"' && !isAtEnd()){
        if (peek() == '\\' && peekNext() == '"') advance();
        advance();
    } 
    advance();
    advance();
    advance();
    return makeFromType(TOKEN_LONG_STRING);
}

static Token checkKeyWord(int start, int end, char* word, TokenType type) {
    if (start + end != scanner.curr - scanner.start) return makeFromType(TOKEN_IDENTIFIER);
    
    for (int i = start; i <= end; i++) {
        if (scanner.start[i] != word[i - start]) return makeFromType(TOKEN_IDENTIFIER);
    }

    return makeFromType(type);
}

static Token makeIdentifier() {
    char ch = scanner.start[0];
    switch (ch)
    {
        case 'D': return checkKeyWord(1, 5, "ouble", TOKEN_TYPE_DOUBLE);
        case 'I': return checkKeyWord(1, 2, "nt", TOKEN_TYPE_INT);
        case 'S': return checkKeyWord(1, 5, "tring", TOKEN_TYPE_STRING);
        case 'n': return checkKeyWord(1, 2, "il", TOKEN_NIL);
        case 'r': return checkKeyWord(1, 5, "eturn", TOKEN_RETURN);
        case 'l': return checkKeyWord(1, 2, "et", TOKEN_LET);
        case 'v': return checkKeyWord(1, 2, "ar", TOKEN_VAR);
        case 'f':
            if (scanner.start[1] == 'u') return checkKeyWord(2, 2, "nc", TOKEN_FUNC);
            else if (scanner.start[1] == 'a') return checkKeyWord(2, 3, "lse", TOKEN_FALSE);
        case 'i': return checkKeyWord(1, 1, "f", TOKEN_IF);
        case 'e': return checkKeyWord(1, 3, "lse", TOKEN_ELSE);
        case 'w': 
            if (scanner.start[1] == 'h') return checkKeyWord(2, 3, "ile", TOKEN_WHILE);
        case 't': return checkKeyWord(1, 3, "rue", TOKEN_TRUE);
    }

    return makeFromType(TOKEN_IDENTIFIER);
}

static Token identifier() {
    while (isAlpha() || isNumber(peek())) advance();
    return makeIdentifier();
}

//returns value of current scanner char
//
static Token scanToken() {
    TokenType type = skipWhiteSpaces();
    if (type == TOKEN_ERROR) return makeFromType(TOKEN_ERROR);

    scanner.start = scanner.curr;

    if (isAtEnd()) return makeFromType(TOKEN_EOF);

    if (isNumber(peek())) return number();
    if (isAlpha()) return identifier();

    char ch = advance();
    switch (ch)
    {
        case '*': return makeFromType(TOKEN_STAR);
        case '+': return makeFromType(TOKEN_PLUS);
        case '-': 
            return match('>')? makeFromType(TOKEN_ARROW): makeFromType(TOKEN_MINUS);
        case '(': return makeFromType(TOKEN_LEFT_PAREN);
        case ')': return makeFromType(TOKEN_RIGHT_PAREN);
        case '{': return makeFromType(TOKEN_LEFT_BRACE);
        case '}': return makeFromType(TOKEN_RIGHT_BRACE);
        case '/': return makeFromType(TOKEN_SLASH);
        case ',': return makeFromType(TOKEN_COMMA);
        case '.': return makeFromType(TOKEN_DOT);
        case ':': return makeFromType(TOKEN_COLON);
        case '\n': return makeFromType(TOKEN_EOL);
        case '?': 
            return match('?')? makeFromType(TOKEN_DOUBLE_QUESTIONS): makeFromType(TOKEN_QUESTION);
        case '!':
            return match('=')? makeFromType(TOKEN_BANG_EQUAL):makeFromType(TOKEN_BANG);
        case '=':
            return match('=')? makeFromType(TOKEN_EQUAL_EQUAL): makeFromType(TOKEN_EQUAL);
        case '<':
            return match('=')? makeFromType(TOKEN_LESS_EQUAL) : makeFromType(TOKEN_LESS);
        case '>':
            return match('=')? makeFromType(TOKEN_GREATER_EQUAL) : makeFromType(TOKEN_GREATER);
        case '"':
            if (peek() == '"' && peekNext() == '"') {
                advance();
                advance();
                // advance();
                // advance();  //escape first newline
                return longString();
            }
            else return string();
        default:
            return makeFromType(TOKEN_ERROR);
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
        if (token.type == TOKEN_ERROR){
            token_delete_tokens(list);
            return NULL;   
        }
        if (token.type == TOKEN_EOF) atEnd = true;
    }

    return list;    
}