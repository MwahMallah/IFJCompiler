#include <stdlib.h>
#include <stdbool.h>
#include "../data_structures/tokenTypes.h"
#include "parser.h"

static int currentToken = 0;
static bool isEOF = false;
static TokenList *tokenList;
static symtable *varTable;
static symtable *funcTable;


static void parseLine();
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

static bool isCurrent(TokenType type){
    return tokenList->tokens[currentToken].type == type;
}

static void isCurrentExit(TokenType type, int exitCode){
    if(isCurrent(type)) return;
    exit(exitCode);
}

static bool isCurrentIncrease(TokenType type){
    if(isCurrent(type)){
        currentToken++;
        return true;
    }
    return false;
}

static void isCurrentIncreaseExit(TokenType type, int exitCode){
    if(isCurrentIncrease(type)) return;
    exit(exitCode);
}


static void expression()



static void variableDeclaration(){
    //considering that current type is let or var
    ValueType varType = NONE_TYPE;
    //check let or var
    bool isConst = isCurrentIncrease(TOKEN_LET);
    //is identifier
    isCurrentExit(TOKEN_IDENTIFIER, 2);
    char *varName = tokenList->tokens[currentToken].lexeme;
    varInfo *info = symtable_get_pair(varTable, varName);
    //check if is not already declared
    if(info){
        exit(3);
    }
    currentToken++;
    //type declaration
    if(isCurrentIncrease(TOKEN_COLON)){
        switch (tokenList->tokens[currentToken].type) {
            case TOKEN_TYPE_STRING:
                varType = STRING;
                break;
            case TOKEN_TYPE_INT:
                varType = INTEGER;
                break;
            case TOKEN_TYPE_DOUBLE:
                varType = FLOAT;
                break;
            default:
                exit(2);
        }
        isCurrentIncrease(TOKEN_QUESTION);
        if(isCurrentIncrease(TOKEN_EOL)){
            return;
        }
    }
    //equal sign
    isCurrentIncreaseExit(TOKEN_EQUAL, 2);
    //todo expression
    //todo add to the table

}

static void assignment(){
    //considering that current type is identifier
    varInfo *info = symtable_get_pair(varTable, tokenList->tokens[currentToken].lexeme);
    if(!info){
        exit(5);
    }
    if(info->isConst){
        exit(9);
    }
    currentToken++;
    isCurrentIncreaseExit(TOKEN_EQUAL, 2);
    //todo exp
}

static void parseBlock(){
    while (!isCurrentIncrease(TOKEN_RIGHT_BRACE)){
        parseLine();
    }
}

static void parseIf(){
    //todo exp
    isCurrentIncrease(TOKEN_EOL);//todo eol???
    isCurrentIncreaseExit(TOKEN_LEFT_BRACE, 2);
    isCurrentIncreaseExit(TOKEN_EOL, 2);//todo not sure
    parseBlock();
    isCurrentIncrease(TOKEN_EOL);//todo eol???
    if(!isCurrentIncrease(TOKEN_ELSE)){
        return;
    }
    isCurrentIncrease(TOKEN_EOL);//todo eol???
    isCurrentIncreaseExit(TOKEN_LEFT_BRACE, 2);
    parseBlock();
    isCurrentIncrease(TOKEN_EOL);
}

static void parseLine(){
    if(isCurrent(TOKEN_VAR) || isCurrent(TOKEN_LET)){
        variableDeclaration();
    } else if(isCurrent(TOKEN_IDENTIFIER)){
        if(tokenList->tokens[currentToken+1].type == TOKEN_LEFT_PAREN){
            //funcCall
        } else{
            assignment();
        }
    } else if(isCurrentIncrease(TOKEN_IF)){
        parseIf();
    }
}

void parse(TokenList *list, symtable *variableTable, symtable *functionTable) {
    tokenList = list;
    varTable = variableTable;
    funcTable = functionTable;
    while (!isCurrent(TOKEN_EOF)) {
        parseLine();
    }
}