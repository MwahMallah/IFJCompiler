#include <stdlib.h>
#include <stdbool.h>
#include "../data_structures/tokenTypes.h"
#include "parser.h"

static int currentToken = 0;
static bool isEOF = false;
static TokenList *tokenList;
static symtable *table;

//typedef struct
//{
//    Token* previous;
//    Token* current;
//} Analyzer;
////global instance of parser
//static Analyzer parser;
//
////moves parser to next token
//static void advance() {
//    parser.previous = parser.current;
//    (parser.current)++;
//}
//
////exits with exitCode, if type is inappropriate
////advances otherwise
//static void consume(TokenType type, int exitCode) {
//    if (parser.current->type == type) {
//        advance();
//        return;
//    } else {
//        exit(exitCode);
//    }
//}
//
//static bool check(TokenType type) {
//    return parser.current->type == type;
//}
//
//static bool match(TokenType type) {
//    if (!check(type)) return false;
//    advance();
//    return true;
//}
//
//static void initParsing(TokenList* userList, symtable* userTable) {
//    parser.previous = userList->tokens;
//    parser.current = (userList->tokens);
//    list = userList;
//    table = userTable;
//}
//
//static void declaration() {
//    if (match(TOKEN_VAR) || match(TOKEN_LET)) {
//
//    } else if (match(TOKEN_EOL)) {
//    } else {
//    }
//}

static bool isCurrentType(TokenType type){
    return tokenList->tokens[currentToken].type == type;
}

static bool isCurrentTypeIncrease(TokenType type){
    if(isCurrentType(type)){
        currentToken++;
        return true;
    }
    return false;
}


static void varDeclaration(){
    if(isCurrentType(TOKEN_IDENTIFIER)){
        //todo check if isn't in the table
        //todo add to the table
        currentToken++;
        if(isCurrentTypeIncrease(TOKEN_COLON)){
            switch (tokenList->tokens[currentToken].type) {
                case TOKEN_TYPE_STRING:
                    //todo add type to the table
                    break;
                case TOKEN_TYPE_INT:
                    //todo add type to the table
                    break;
                case TOKEN_TYPE_DOUBLE:
                    //todo add type to the table
                    break;
                default:
                    exit(2);
            }
        }
        if(!isCurrentTypeIncrease(TOKEN_EQUAL))
    } else{

    }
}

static void parseLine(){
    if(isCurrentType(TOKEN_VAR)){
        currentToken++;
        varDeclaration();
    }
}

void parse(TokenList *list, symtable *symTable) {
    tokenList = list;
    table = symTable;
    while (!isCurrentType(TOKEN_EOF)) {

    }
}