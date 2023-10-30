#include <stdio.h>
#include <stdbool.h>
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

static bool check(TokenType type) {
    return parser.current->type == type;
}

static bool match(TokenType type) {
    if (!check(type)) return false;
    advance();
    return true;
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
static void statement();
static void declaration();
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

static void string() {
    printf("PUSHS string@%s\n", parser.previous->lexeme);
}

static void variable() {

    Token* var = parser.previous;

    if (match(TOKEN_EQUAL)) {
        expression();
        printf("POPS GF@%s\n", var->lexeme);
    } else {
        printf("PUSHS GF@%s\n", var->lexeme);
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
    Token* value = parser.current;
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
        case TOKEN_PLUS: 
            if (value->type == TOKEN_STRING) {
                printf("POPS GF@tmp_op1\n");
                printf("POPS GF@tmp_op2\n");
                printf("CONCAT GF@tmp_op3 GF@tmp_op2 GF@tmp_op1\n");
                printf("PUSHS GF@tmp_op3\n"); 
                break;
            } else {
                printf("ADDS\n"); break;    
            }
        case TOKEN_MINUS: printf("SUBS\n"); break;
        case TOKEN_STAR: printf("MULS\n"); break;
        case TOKEN_SLASH: 
            if (value->type == TOKEN_INTEGER) {
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
    [TOKEN_STRING] = {string, NULL, PREC_NONE},
    [TOKEN_IDENTIFIER] = {variable, NULL, PREC_NONE},
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

static void variableDeclaration() {
    Token* var = parser.current;
    advance(); //check variable type next
    printf("DEFVAR GF@%s\n", var->lexeme);

    bool declaredType = false;

    if (match(TOKEN_COLON) && (match(TOKEN_TYPE_DOUBLE) || match(TOKEN_TYPE_INT) || match(TOKEN_TYPE_STRING))) {
        declaredType = true;
    }

    if (match(TOKEN_EQUAL)) {
        expression();
    } else {
        printf("PUSHS nil@nil\n");     
    }

    printf("POPS GF@%s\n", var->lexeme);
    if (check(TOKEN_EOF) || match(TOKEN_EOL));
}

static void writeStatement() {
    expression();
    if (check(TOKEN_EOF) || match(TOKEN_EOL)) {
        printf("POPS GF@tmp_op3\n");
        printf("WRITE GF@tmp_op3\n");
    }
    if (check(TOKEN_EOF) || match(TOKEN_EOL));
}

static void expressionStatement() {
    expression();
    if (check(TOKEN_EOF) || match(TOKEN_EOL));
}

static void declaration() {
    if (match(TOKEN_VAR) || match(TOKEN_LET)) {
        variableDeclaration();
    } else if (match(TOKEN_EOL)) {
    } else {
        statement();
    }
}

static void statement() {
    if (match(TOKEN_WRITE)) {
        writeStatement();
    } else {
        expressionStatement();
    }
}

//initialises parser to first token in the list, writes header to output file
static void initCompiler(TokenList* userList) {
    parser.previous = userList->tokens;
    parser.current = (userList->tokens);
    list = userList;

    printf(".IFJcode23\n\n");
    printf("DEFVAR GF@tmp_op1\n");
    printf("DEFVAR GF@tmp_op2\n");
    printf("DEFVAR GF@tmp_op3\n");
}

//ends compilation process
static void endCompilation() {

}

//public function for compiling list of tokens
int compile(TokenList* list) {
    initCompiler(list);

    // advance();
    while (!match(TOKEN_EOF)) {
        declaration();
    }
    
    endCompilation();
}