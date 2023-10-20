#include "compiler.h"
#include <stdio.h>
#include "../test/debug.h"

//enum that stores precedence of various operations
//greater value of enum type itself means greater precedence
typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT, // =
    PREC_EQUALITY, // == !=
    PREC_COMPARISON, // < > <= >=
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
        printf("Expected EOF\n");
    }
}

//function, that adds push instruction to output file
//pushes number value to vm stack
static void number() {
    printf("PUSHS int@%.*s\n", parser.previous->length, parser.previous->start);
}

static void expression();
static ParseRule* getRule(TokenType type);
static void parsePrecedence(Precedence precedence);

static void binary() {
    TokenType operator = parser.previous->type;
    ParseRule* rule = getRule(operator);
    parsePrecedence((Precedence)(rule->precedence + 1));

    switch (operator)
    {
        case TOKEN_PLUS: printf("ADDS\n"); break;
        case TOKEN_MINUS: printf("SUBS\n"); break;
        case TOKEN_STAR: printf("MULS\n"); break;
        case TOKEN_SLASH: printf("IDIVS\n"); break;
        default: return;
    }
}

ParseRule rules[] = {
    [TOKEN_NUMBER] = {number, NULL, PREC_NONE},
    [TOKEN_PLUS] = {NULL, binary, PREC_TERM},
    [TOKEN_MINUS] = {NULL, binary, PREC_TERM},
    [TOKEN_STAR] = {NULL, binary, PREC_FACTOR},
    [TOKEN_SLASH] = {NULL, binary, PREC_FACTOR},
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