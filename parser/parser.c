#include <stdlib.h>
#include <stdbool.h>
#include "../data_structures/tokenTypes.h"
#include "parser.h"

typedef struct 
{
    Token* previous;
    Token* current;
} Analyzer;


//global instance of parser
static Analyzer parser;
static TokenList* list;
symtable* table;

//moves parser to next token
static void advance() {
    parser.previous = parser.current;
    (parser.current)++;
}

//exits with exitCode, if type is inappropriate
//advances otherwise
static void consume(TokenType type, int exitCode) {
    if (parser.current->type == type) {
        advance();
        return;
    } else {
        exit(exitCode);
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

static void initParsing(TokenList* userList, symtable* userTable) {
    parser.previous = userList->tokens;
    parser.current = (userList->tokens);
    list = userList;
    table = userTable;
}

static void variableDeclaration() {
    Token newVar = consume(TOKEN_IDENTIFIER, 2);
    if (match(TOKEN_COLON)) {

    }

    //symtable.addEntry(newVar, type)
}

static void funcDeclaration() {


    //symtable.addFunc()
}

static void statement() {
    if (match(TOKEN_WHILE)) {
        whileStmt();
    }
}

static void declaration() {
    if (match(TOKEN_VAR) || match(TOKEN_LET)) {
        variableDeclaration();
    } else if (match(TOKEN_FUNC)) {
        funcDeclaration();
    } else if (match(TOKEN_EOL)) {
    } else {
        statement();
    }
}

void parse(TokenList* list, symtable* table) {
    initParsing(list, table);

    while (!match(TOKEN_EOF)) {
        declaration();   
    }
}