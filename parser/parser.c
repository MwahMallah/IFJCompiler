#include <stdlib.h>
#include <stdbool.h>
#include "../data_structures/tokenTypes.h"
#include "parser.h"

static int currentToken = 0;
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

static ValueType getTypeFromCurrent(){
    switch (tokenList->tokens[currentToken].type) {
        case TOKEN_TYPE_STRING:
            return STRING;
        case TOKEN_TYPE_INT:
            return INTEGER;
        case TOKEN_TYPE_DOUBLE:
            return FLOAT;
        default:
            return NONE_TYPE;
    }
}


static bool isCurrentOperation(){
    return isCurrent(TOKEN_PLUS) || isCurrent(TOKEN_MINUS) || isCurrent(TOKEN_STAR) || isCurrent(TOKEN_SLASH);
}

static void expression(){
    ValueType expressionType = NONE_TYPE;
    while (isCurrentOperation() || isCurrent(TOKEN_INTEGER) || isCurrent(TOKEN_STRING) || isCurrent(TOKEN_FLOAT)){

    }
//    int countOfBrackets = 0;
//    if(isCurrentIncrease(TOKEN_LEFT_PAREN)){
//        countOfBrackets++;
//    }
//    ValueType expressionType = getTypeFromCurrent();
//    if(expressionType == NONE_TYPE){
//        exit(2);
//    }
//    while (true){
//        if(isCurrent(TOKEN_IDENTIFIER)){
//            //todo check of variable
//        } else{
//            ValueType temp = getTypeFromCurrent();
//            if(temp == NONE_TYPE){
//                exit(2);
//            }
//            if(expressionType == NONE_TYPE){
//                expressionType = temp;
//            } else if()
//        }
//        currentToken++;
//        if(isCurrentIncrease(TOKEN_RIGHT_PAREN)){
//            if(countOfBrackets == 0){
//                exit(2);
//            }
//        }
//        if(!isCurrentOperation()){
//            exit(2);
//        }
//
//    }
}



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
        varType = getTypeFromCurrent();
        currentToken++;
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
    isCurrentIncrease(TOKEN_EOL);//todo eol???
    isCurrentIncreaseExit(TOKEN_LEFT_BRACE, 2);
    isCurrentIncrease(TOKEN_EOL);//todo not sure
    while (!isCurrentIncrease(TOKEN_RIGHT_BRACE)){
        parseLine();
    }
}

static void parseIf(){
    //todo exp
    parseBlock();
    if(isCurrentIncrease(TOKEN_EOL)){
        if(!isCurrentIncrease(TOKEN_ELSE)){
            return;
        }
    } else{
        isCurrentIncreaseExit(TOKEN_ELSE, 2);
    }
    parseBlock();
    isCurrentIncreaseExit(TOKEN_EOL, 2);
}

static void parseWhile(){
    //todo exp
    parseBlock();
    isCurrentIncreaseExit(TOKEN_EOL, 2);
}

static void funcDeclaration(){
    isCurrentExit(TOKEN_IDENTIFIER, 2);
    char *funcName = tokenList->tokens[currentToken].lexeme;
    funcInfo *info = symtable_get_pair(funcTable, funcName);
    if(info){
        exit(9);//todo not sure
    }
    currentToken++;
    isCurrentIncreaseExit(TOKEN_LEFT_PAREN, 2);


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
    } else if(isCurrentIncrease(TOKEN_WHILE)){
        parseWhile();
    } else if(isCurrentIncrease(TOKEN_FUNC)){
        funcDeclaration();
    }
}

void parse(TokenList *list, symtable *variableTable, symtable *functionTable) {
    tokenList = list;
    varTable = variableTable;
    funcTable = functionTable;
    while (!isCurrent(TOKEN_EOF)) {
        parseLine();
        currentToken++;
    }
}