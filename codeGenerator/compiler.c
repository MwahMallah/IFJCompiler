#include <stdio.h>
#include "compiler.h"
#include "../test/debug.h"
#include "../data_structures/str.h"

//enum that stores precedence of various operations
//greater value of enum type itself means greater precedence
typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT, // =
    PREC_COMPARISON, // < > <= >= == !=
    PREC_TERM, // + -
    PREC_FACTOR, // * /
    PREC_UNARY, // ! -
    PREC_GROUPING, // ()
    PREC_PRIMARY
} Precedence;

typedef void (*ParseFn)();

//struct that dictates parsing rule for various operation
typedef struct {
    ParseFn prefix; //function for parsing operation as prefix
    ParseFn infix; //function for parsing operation as infix 
    Precedence precedence; //precedence of operation
} ParseRule;

//struct that represents parser, moving through list of all tokens
typedef struct 
{
    Token* previous;
    Token* current;
} Parser;

//global instance of parser
Parser parser;
TokenList* list;

//moves parser to next token
static void advance() {
    parser.previous = parser.current;
    (parser.current)++;
}

static void consume(TokenType type) {
    if (parser.current->type == type) {
        advance();
        return;
    } else {
        printf("Expected token\n");
    }
}

//function, that adds push instruction to output file
//pushes integer value to vm stack
static void integer() {
    printf("PUSHS int@%s\n", parser.previous->lexeme);
}

//function, that adds push instruction to output file
//pushes float value to vm stack
static void floating() {
    double value = strtodouble(parser.previous->lexeme);
    printf("PUSHS float@%a\n", value);
}

static void expression();
static ParseRule* getRule(TokenType type);
static void parsePrecedence(Precedence precedence);

//parses literal expression
static void literal() {
    switch (parser.previous->type)
    {
        case TOKEN_TRUE: printf("PUSHS bool@%s\n", parser.previous->lexeme); break;
        case TOKEN_FALSE: printf("PUSHS bool@%s\n", parser.previous->lexeme); break;
        case TOKEN_NIL: printf("PUSHS nil@%s\n", parser.previous->lexeme); break;
        default: return;
    }
}

static void unary() {
    TokenType operator = parser.previous->type;

    if (operator == TOKEN_MINUS) {
        addMinus(parser.current);
    }
    parsePrecedence(PREC_UNARY);
}

//parses grouping expression
static void grouping() {
    expression();
    consume(TOKEN_RIGHT_PAREN);
}

//parses binary expression
static void binary() {
    TokenType operator = parser.previous->type;
    TokenType valueType = parser.current->type;
    ParseRule* rule = getRule(operator);
    parsePrecedence((Precedence)(rule->precedence + 1));

    switch (operator)
    {
        case TOKEN_LESS: printf("LTS\n"); break;
        case TOKEN_GREATER: printf("GTS\n"); break;
        case TOKEN_EQUAL_EQUAL: printf("EQS\n"); break;
        case TOKEN_BANG_EQUAL: printf("EQS\nNOTS\n"); break;
        case TOKEN_LESS_EQUAL: printf("GTS\nNOTS\n"); break;
        case TOKEN_GREATER_EQUAL: printf("LTS\nNOTS\n"); break;
        case TOKEN_PLUS: printf("ADDS\n"); break;    
        case TOKEN_MINUS: printf("SUBS\n"); break;
        case TOKEN_STAR: printf("MULS\n"); break;
        case TOKEN_SLASH: 
            if (valueType == TOKEN_INTEGER) {
                printf("IDIVS\n"); break;
            } else {
                printf("DIVS\n"); break;
            }
        default: return;
    }
}

ParseRule rules[] = {
    [TOKEN_FLOAT] = {floating, NULL, PREC_NONE},
    [TOKEN_INTEGER] = {integer, NULL, PREC_NONE},
    [TOKEN_TRUE] = {literal, NULL, PREC_NONE},
    [TOKEN_FALSE] = {literal, NULL, PREC_NONE},
    [TOKEN_NIL] = {literal, NULL, PREC_NONE},    
    [TOKEN_PLUS] = {NULL, binary, PREC_TERM},
    [TOKEN_MINUS] = {unary, binary, PREC_TERM},
    [TOKEN_STAR] = {NULL, binary, PREC_FACTOR},
    [TOKEN_SLASH] = {NULL, binary, PREC_FACTOR},
    [TOKEN_EQUAL_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_BANG_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LEFT_PAREN] = {grouping, NULL, PREC_NONE},
    [TOKEN_RIGHT_PAREN] = {NULL, NULL, PREC_NONE},
    [TOKEN_EOF] = {NULL, NULL, PREC_NONE}
};

//returns parsing rule for this operation
static ParseRule* getRule(TokenType type) {
    return &rules[type];
}

static void parsePrecedence(Precedence precedence) {
    advance();

    //gets first token prefix rule and executes it
    ParseFn prefixOperation = getRule(parser.previous->type)->prefix;
    prefixOperation();

    while (precedence <= getRule(parser.current->type)->precedence)
    {
        advance();
        ParseFn infixRule = getRule(parser.previous->type)->infix;
        infixRule();
    }
    
}

static void expression() {
    parsePrecedence(PREC_ASSIGNMENT);
}

//initialises parser to first token in the list, writes header to output file
static void initCompiler(TokenList* userList) {
    parser.previous = userList->tokens;
    parser.current = (userList->tokens);
    list = userList;

    printf(".IFJcode23\n\n");
    printf("DEFVAR GF@var\n");
}

//ends compilation process
static void endCompilation() {
    printf("POPS GF@var\n");
    printf("WRITE GF@var\n");
}

//public function for compiling list of tokens
int compile(TokenList* list) {
    initCompiler(list);

    // advance();
    expression();
    consume(TOKEN_EOF);

    endCompilation();
}