#include <stdio.h>
#include <stdbool.h>
#include "compiler.h"
#include "../data_structures/str.h"
#include "../data_structures/valueTypes.h"

// typedef enum {
//     STRING,
//     INTEGER,
//     FLOAT,
//     NONE_TYPE
// } ValueType;

//enum that stores precedence of various operations
//greater value of enum type itself means greater precedence
typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT, // =
    PREC_DOUBLE_QUESTIONS,
    PREC_COMPARISON, // < > <= >= == !=
    PREC_TERM, // + -
    PREC_FACTOR, // * /
    PREC_UNARY, // -
    PREC_CALL,
    PREC_GROUPING, // ()
    PREC_PRIMARY
} Precedence;

typedef ValueType (*ParseFn)(Token*);

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

//struct that represents current locals
typedef struct 
{
    Token variable;
    int depth;
    ValueType type;
} Local;

typedef struct 
{
    Local variables[256];
    int scopeDepth;
    int localPos;
} LocalList;

//global instance of parser
static Parser parser;
static TokenList* list;
static LocalList locals;
static int jumpNumber;
static int questionLabel;
static int substringLabel;

//pushes variable to list of local variables
static void pushLocal(Token* variable, ValueType declaredType) {
    Local newLocal;
    newLocal.variable = *variable;
    newLocal.depth = locals.scopeDepth;
    newLocal.type = declaredType;
    locals.variables[++locals.localPos] = newLocal;
}

//searches through local variables
static bool variableIsLocal(Token* variable) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return true;
        }
    }
    return false;
}

static int getVarDepth(Token* variable) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return locals.variables[i].depth;
        }
    }
    return 0;
}

static ValueType getVarType(Token* variable) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return locals.variables[i].type;
        }
    }
    return NONE_TYPE;
}

static bool variableIsType(Token* variable, ValueType type) {
    if (variableIsLocal(variable)) {
        return getVarType(variable) == type;
    }
}


static bool isNative(char* funcName) {
    if (
    compare_strings(funcName, "readInt"   ) == 1 || 
    compare_strings(funcName, "write"     ) == 1 || 
    compare_strings(funcName, "readDouble") == 1 || 
    compare_strings(funcName, "readString") == 1 || 
    compare_strings(funcName, "Int2Double") == 1 ||
    compare_strings(funcName, "Double2Int") == 1 ||
    compare_strings(funcName, "chr"       ) == 1 ||
    compare_strings(funcName, "ord"       ) == 1 ||
    compare_strings(funcName, "length"    ) == 1 ||
    compare_strings(funcName, "substring" ) == 1 ) {
        return true;
    } else {
        return false;
    }
}

static ValueType nativeFunc(char* funcName, int numArgs) {
    // printf("PUSHFRAME\n");
    if (compare_strings(funcName, "write") == 1) {
        for (int i = 1; i < numArgs; i++) {
            printf("WRITE TF@%%%d\n", i);
        }
        return NONE_TYPE;
    } else if (compare_strings(funcName, "readInt") == 1) {
        printf("READ GF@tmp_op1 int\n");
        printf("PUSHS GF@tmp_op1\n");
        return INTEGER;
    } else if (compare_strings(funcName, "readString") == 1) {
        printf("READ GF@tmp_op1 string\n");
        printf("PUSHS GF@tmp_op1\n");
        return STRING;
    } else if (compare_strings(funcName, "readDouble") == 1) {
        printf("READ GF@tmp_op1 float\n");
        printf("PUSHS GF@tmp_op1\n");
        return FLOAT;
    } else if (compare_strings(funcName, "Int2Double") == 1) {
        printf("PUSHS TF@%%%d\n", 1);
        printf("INT2FLOATS\n");
        return FLOAT;
    } else if (compare_strings(funcName, "Double2Int")  == 1) {
        printf("FLOAT2INT GF@tmp_op1 TF@%%%d\n", 1);
        printf("PUSHS GF@tmp_op1\n");
        return INTEGER;
    } else if (compare_strings(funcName, "chr") == 1) {
        printf("PUSHS TF@%%%d\n", 1);
        printf("INT2CHARS\n");
        return STRING;
    } else if (compare_strings(funcName, "length") == 1) {
        printf("STRLEN GF@tmp_op1 TF@%%%d\n", 1);
        printf("PUSHS GF@tmp_op1\n");
        return INTEGER;
    } else if (compare_strings(funcName, "ord") == 1) {
        printf("PUSHS TF@%%%d\n", 1);
        printf("PUSHS int@0\n");
        printf("STRI2INTS\n");
        return INTEGER;
    } else if (compare_strings(funcName, "substring") == 1) {
        printf("PUSHS string@\n");
        printf("POPS GF@tmp_op1\n");
        printf("LABEL %%substring$%d\n", substringLabel);
        printf("PUSHS TF@%%2\n");
        printf("PUSHS TF@%%3\n");
        printf("JUMPIFEQS %%substringEnd$%d\n", substringLabel);
        printf("GETCHAR GF@tmp_op2 TF@%%1 TF@%%2\n");  //tmp_op2 = string[i]
        printf("CONCAT GF@tmp_op1 GF@tmp_op1 GF@tmp_op2\n");
        printf("ADD TF@%%2 TF@%%2 int@1\n");
        printf("JUMP %%substring$%d\n", substringLabel);
        printf("LABEL %%substringEnd$%d\n", substringLabel++);
        printf("PUSHS GF@tmp_op1\n");
        return STRING;
    }

    // printf("POPFRAME\n");
}

//pops local variable frame
static void popLocalFrame() {
    // printf("POPFRAME\n");
    locals.scopeDepth -= 1;
    int i;
    for (i = locals.localPos; i >= 0; i--) { //finds position where last frame was
        if (locals.variables[i].depth == locals.scopeDepth) break;
    }

    locals.localPos = i; //sets current local position to end of previous frame
}

//creates local variable frame
static void createLocalFrame() {
    // printf("CREATEFRAME\nPUSHFRAME\n");
    locals.scopeDepth += 1;
}

//moves parser to next token
static Token* advance() {
    Token* returnedToken = parser.previous;
    parser.previous = parser.current;
    (parser.current)++;
    return returnedToken;
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

static bool type(ValueType* declaredType) {
    if (match(TOKEN_TYPE_DOUBLE)) {
        match(TOKEN_QUESTION);
        *declaredType = FLOAT;
        return true;
    } else if (match(TOKEN_TYPE_STRING)) {
        match(TOKEN_QUESTION);
        *declaredType = STRING;
        return true;
    } else if (match(TOKEN_TYPE_INT)) {
        match(TOKEN_QUESTION);
        *declaredType = INTEGER;
        return true;
    }

    return false;
}

static void skipFunctionDecl() {
    while (!match(TOKEN_LEFT_BRACE)) advance();
    int unclosedBraces = 1;

    while (unclosedBraces != 0){
        if (check(TOKEN_LEFT_BRACE)) unclosedBraces++;
        else if (check(TOKEN_RIGHT_BRACE)) unclosedBraces--;
        advance();
    }
}

//function, that adds push instruction to output file
//pushes integer value to vm stack
static ValueType integer(Token* name) {
    printf("PUSHS int@%s\n", parser.previous->lexeme);
    return INTEGER;
}

//function, that adds push instruction to output file
//pushes float value to vm stack
static ValueType floating(Token* name) {
    double value = strtodouble(parser.previous->lexeme);
    printf("PUSHS float@%a\n", value);
    return FLOAT;
}

static ValueType expression();
static void statement(bool isFirstFrame);
static void declaration(bool isLocal, bool isFirstFrame);
static ParseRule* getRule(TokenType type);
static ValueType parsePrecedence(Precedence precedence);
static void variableDeclaration(bool isLocal, bool inFunctionParams);

//parses literal expression
static ValueType literal(Token* name) {
    switch (parser.previous->type)
    {
        case TOKEN_TRUE: printf("PUSHS bool@%s\n", parser.previous->lexeme); break;
        case TOKEN_FALSE: printf("PUSHS bool@%s\n", parser.previous->lexeme); break;
        case TOKEN_NIL: printf("PUSHS nil@%s\n", parser.previous->lexeme); break;
        default: break;
    }
    
    return NONE_TYPE;
}

static ValueType string(Token* name) {
    printf("PUSHS string@%s\n", parser.previous->lexeme);
    return STRING;
}

static ValueType variable(Token* name) {
    Token* var = parser.previous;

    if (check(TOKEN_LEFT_PAREN)) {
        return NONE_TYPE;
    }

    if (match(TOKEN_EQUAL)) {
        expression();
        if (variableIsLocal(var)) {
            printf("POPS LF@%s$%d\n", var->lexeme, getVarDepth(var));
        } else {
            printf("POPS GF@%s\n", var->lexeme);
        }
    } else {
        if (variableIsLocal(var)) {
            printf("PUSHS LF@%s$%d\n", var->lexeme, getVarDepth(var));
        } else {
            printf("PUSHS GF@%s\n", var->lexeme);
        }
    }

    return NONE_TYPE;
}

static ValueType unary(Token* name) {
    TokenType operator = parser.previous->type;
    Token* rightValue = parser.current;

    if (operator == TOKEN_MINUS) {
        if (rightValue->type == TOKEN_FLOAT || variableIsType(rightValue, FLOAT)) {
            printf("PUSHS float@0x0p+0\n");
        } else if (rightValue->type == TOKEN_INTEGER || variableIsType(rightValue, INTEGER)) {
            printf("PUSHS int@0\n");
        }
    }
    
    ValueType type = parsePrecedence(PREC_UNARY);
    printf("SUBS\n");
    return type;
}

//parses grouping expression
static ValueType grouping(Token* name) {
    ValueType type = expression();
    consume(TOKEN_RIGHT_PAREN);
    return type;
}

//parses binary expression
static ValueType binary(Token* leftValue) {
    TokenType operator = parser.previous->type;
    Token* rightValue = parser.current;
    ParseRule* rule = getRule(operator);
    ValueType rightValueType = parsePrecedence((Precedence)(rule->precedence + 1));
    ValueType binaryOpType = NONE_TYPE;

    //implicitly cast integer to double
    if ((leftValue->type == TOKEN_FLOAT || variableIsType(leftValue, FLOAT)) && rightValueType == INTEGER) {
        binaryOpType = FLOAT;
        printf("INT2FLOATS\n");
        if (rightValue->type == TOKEN_INTEGER) rightValue->type = TOKEN_FLOAT;
    } else if ((leftValue->type == TOKEN_INTEGER || variableIsType(leftValue, INTEGER)) && rightValueType == FLOAT) {
        binaryOpType = FLOAT;
        printf("POPS GF@tmp_op1\n"); //right value
        printf("INT2FLOATS\n"); //left value to float
        printf("PUSHS GF@tmp_op1\n");
        if (leftValue->type == TOKEN_INTEGER) leftValue->type = TOKEN_FLOAT;
    }

    switch (operator)
    {
        case TOKEN_LESS: printf("LTS\n"); break;
        case TOKEN_GREATER: printf("GTS\n"); break;
        case TOKEN_EQUAL_EQUAL: printf("EQS\n"); break;
        case TOKEN_BANG_EQUAL: printf("EQS\nNOTS\n"); break;
        case TOKEN_LESS_EQUAL: printf("GTS\nNOTS\n"); break;
        case TOKEN_GREATER_EQUAL: printf("LTS\nNOTS\n"); break;
        case TOKEN_DOUBLE_QUESTIONS:
            printf("POPS GF@tmp_op2\n"); //right_operand
            printf("POPS GF@tmp_op1\n"); //left_operand
            printf("JUMPIFNEQ %%left_op$%d nil@nil GF@tmp_op1\n", questionLabel);   
            printf("PUSHS GF@tmp_op2\n");
            printf("JUMP %%right_op$%d\n", questionLabel);
            printf("LABEL %%left_op$%d\n", questionLabel);
            printf("PUSHS GF@tmp_op1\n");
            printf("LABEL %%right_op$%d\n", questionLabel++);
            if (leftValue->type == TOKEN_STRING || variableIsType(leftValue, STRING)) return STRING;
            if (leftValue->type == TOKEN_INTEGER || variableIsType(leftValue, INTEGER)) return INTEGER;
            if (leftValue->type == TOKEN_FLOAT || variableIsType(leftValue, FLOAT)) return FLOAT;
            break;
        case TOKEN_PLUS: 
            if ((leftValue->type == TOKEN_STRING || variableIsType(leftValue, STRING)) && rightValueType == STRING) {
                binaryOpType = STRING;
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
            if ((leftValue->type == TOKEN_INTEGER || variableIsType(leftValue, INTEGER)) && rightValueType == INTEGER) {
                binaryOpType = INTEGER;
                printf("IDIVS\n"); break;
            } else {
                binaryOpType = FLOAT;
                printf("DIVS\n"); break;
            }
        default: break;
    }

    return binaryOpType;
}

static ValueType call(Token* funcName) {
    ValueType returnType = NONE_TYPE;
    int argumentNum = 1;
    printf("CREATEFRAME\n");
    if (isNative(funcName->lexeme)) {
        if (!check(TOKEN_RIGHT_PAREN)) {
            do {
                printf("DEFVAR TF@%%%d\n", argumentNum);
                expression();
                printf("POPS TF@%%%d\n", argumentNum++);
            } while (match(TOKEN_COMMA));
        }

        returnType = nativeFunc(funcName->lexeme, argumentNum);
    } else {
        printf("PUSHFRAME\n");

        if (!check(TOKEN_RIGHT_PAREN)) {
            do {
                printf("DEFVAR LF@%%%d\n", argumentNum);
                expression();
                printf("POPS LF@%%%d\n", argumentNum++);
            } while (match(TOKEN_COMMA));
        }

        printf("CALL $%s\n", funcName->lexeme);
        printf("PUSHS TF@%%retval\n");
    }

    consume(TOKEN_RIGHT_PAREN);
    return returnType;
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
    [TOKEN_DOUBLE_QUESTIONS] = {NULL, binary, PREC_DOUBLE_QUESTIONS},
    [TOKEN_EQUAL_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_BANG_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LEFT_PAREN] = {grouping, call, PREC_CALL},
    [TOKEN_RIGHT_PAREN] = {NULL, NULL, PREC_NONE},
    [TOKEN_EOF] = {NULL, NULL, PREC_NONE}
};

//returns parsing rule for this operation
static ParseRule* getRule(TokenType type) {
    return &rules[type];
}

static ValueType parsePrecedence(Precedence precedence) {
    advance();

    //gets first token prefix rule and executes it
    ParseFn prefixOperation = getRule(parser.previous->type)->prefix;
    ValueType prefixType = prefixOperation(NULL);
    ValueType infixType = NONE_TYPE;
    Token* name;

    while (precedence <= getRule(parser.current->type)->precedence)
    {
        name = advance();
        ParseFn infixRule = getRule(parser.previous->type)->infix;
        infixType = infixRule(name);
    }

    return infixType == NONE_TYPE? prefixType : infixType;
}

static ValueType expression() {
    return parsePrecedence(PREC_ASSIGNMENT);
}

static void block() {
    while (!match(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
        declaration(true, false);
    }
}

static void funcDeclaration() {
    Token* funcName = parser.current;
    match(TOKEN_IDENTIFIER);

    printf("LABEL $%s\n", funcName->lexeme);
    // printf("PUSHFRAME\n");
    printf("DEFVAR LF@%%retval\n");

    int argumentNum = 1;
    consume(TOKEN_LEFT_PAREN);
    if (!check(TOKEN_RIGHT_PAREN)) {
        do
        {
            if (match(TOKEN_IDENTIFIER) || match(TOKEN_WITH));
            Token* arg = parser.current; //current arg
            variableDeclaration(true, true);
            printf("MOVE LF@%s$%d LF@%%%d\n", arg->lexeme, getVarDepth(arg), argumentNum++);
        } while(match(TOKEN_COMMA));
    }
    consume(TOKEN_RIGHT_PAREN);
    consume(TOKEN_ARROW);
    advance(); // skip return type
    consume(TOKEN_LEFT_BRACE);
    block();
    printf("POPFRAME\n");
    printf("RETURN\n");
}

static void variableDeclaration(bool isLocal, bool inFunctionParams) {
    Token* var = parser.current;
    advance(); //check variable type next
    if (isLocal) {
        printf("DEFVAR LF@%s$%d\n", var->lexeme, locals.scopeDepth);
    } else {
        printf("DEFVAR GF@%s\n", var->lexeme);
    }

    ValueType declaredType;
    ValueType expressionType;

    if (match(TOKEN_COLON)) {
        type(&declaredType);
    } else {
        declaredType = NONE_TYPE;
    }

    // if (!inFunctionParams) {
    if (match(TOKEN_EQUAL)) {
        expressionType = expression();
        if (expressionType == FLOAT && declaredType == INTEGER) {
            printf("FLOAT2INTS\n");
        }
        else if (expressionType == INTEGER && declaredType == FLOAT) printf("INT2FLOATS\n");
    } else {
        printf("PUSHS nil@nil\n");     
    }

    if (isLocal) {
        pushLocal(var, declaredType == NONE_TYPE? expressionType : declaredType);
        printf("POPS LF@%s$%d\n", var->lexeme, getVarDepth(var));
    } else {
        printf("POPS GF@%s\n", var->lexeme);
    }

    if (check(TOKEN_EOF) || match(TOKEN_EOL));
    // }    
}

static void ifStatement() {
    if (match(TOKEN_LET)) {
        printf("PUSHS nil@nil\n");
        advance();
        variable(NULL);
    } else if (match(TOKEN_LEFT_PAREN)) {
        expression();
        match(TOKEN_RIGHT_PAREN);
        printf("PUSHS bool@false\n"); //JUMPIFNEQS takes two values from stack, so we push one more
    }

    int ifStmtNum = jumpNumber++;

    printf("JUMPIFEQS elseJump%d\n", ifStmtNum); //escapes then statement

    match(TOKEN_EOL); //if there is EOL doesn't matter
    match(TOKEN_LEFT_BRACE);
    createLocalFrame();
    block();
    popLocalFrame();
    printf("JUMP thenJump%d\n", ifStmtNum); //escapes else statement

    printf("LABEL elseJump%d\n", ifStmtNum); //label to jump to
    if (match(TOKEN_ELSE)) {
        match(TOKEN_EOL); //if here is EOL doesn't matter
        match(TOKEN_LEFT_BRACE);
        createLocalFrame();
        block();
        popLocalFrame();
    }

    printf("LABEL thenJump%d\n", ifStmtNum);
}

static void returnStatement() {
    if (match(TOKEN_EOL)) {
        printf("PUSHS nil@nil\n");
        printf("POPS LF@%%retval\n");
    } else {
        expression();
        printf("POPS LF@%%retval\n");
    }
}

static void whileStatement() {
    int whileStmtNumber = jumpNumber++;
    match(TOKEN_LEFT_PAREN);
    printf("LABEL whileStart%d\n", whileStmtNumber);
    expression();
    match(TOKEN_RIGHT_PAREN);
    printf("PUSHS bool@false\n");

    printf("JUMPIFEQS whileEnd%d\n", whileStmtNumber); //escapes then statement

    match(TOKEN_EOL); //if here is EOL doesn't matter
    match(TOKEN_LEFT_BRACE);
    createLocalFrame();
    block();
    popLocalFrame();
    printf("JUMP whileStart%d\n", whileStmtNumber); //escapes else statement

    printf("LABEL whileEnd%d\n", whileStmtNumber); //label to jump to
}

static void expressionStatement() {
    expression();
    if (check(TOKEN_EOF) || match(TOKEN_EOL));
}

static void declaration(bool isLocal, bool isFirstFrame) {
    if (match(TOKEN_FUNC)) {
        while (!match(TOKEN_RIGHT_BRACE)) advance();
    } else if (match(TOKEN_VAR) || match(TOKEN_LET)) {
        variableDeclaration(isLocal, false);
    } else if (match(TOKEN_EOL)) {
    } else {
        statement(isFirstFrame);
    }
}

static void statement(bool isFirstFrame) {
    if (match(TOKEN_IF)) {
        if (isFirstFrame) printf("CREATEFRAME\nPUSHFRAME\n");
        ifStatement();
        if (isFirstFrame) printf("POPFRAME\n");
    } else if (match(TOKEN_RETURN)) {
        returnStatement();
    } else if (match(TOKEN_WHILE)) {
        if (isFirstFrame) printf("CREATEFRAME\nPUSHFRAME\n");
        whileStatement();
        if (isFirstFrame) printf("POPFRAME\n");
    } else if (match(TOKEN_LEFT_BRACE)) {
        createLocalFrame();
        block();
        popLocalFrame();
    } else {
        expressionStatement();
    }
}

//initialises parser to first token in the list, writes header to output file
static void initCompiler(TokenList* userList) {
    parser.previous = userList->tokens;
    parser.current = userList->tokens;
    locals.localPos = -1;
    locals.scopeDepth = 0;
    list = userList;
    jumpNumber = 0;
    questionLabel = 0;
    substringLabel = 0;

    printf(".IFJcode23\n\n");
    printf("DEFVAR GF@tmp_op1\n");
    printf("DEFVAR GF@tmp_op2\n");
    printf("DEFVAR GF@tmp_op3\n");
    printf("JUMP $$main\n");
}

static void restartCompiler(TokenList* userList) {
    parser.previous = userList->tokens;
    parser.current = userList->tokens;
    locals.localPos = -1;
    locals.scopeDepth = 0;
    list = userList;
}

//ends compilation process
static void endCompilation() {

}

//public function for compiling list of tokens
int compile(TokenList* list) {
    initCompiler(list);

    while (!match(TOKEN_EOF)) {
        if (match(TOKEN_FUNC)) funcDeclaration();
        else advance();
    }

    restartCompiler(list);

    printf("LABEL $$main\n");
    // advance();
    while (!match(TOKEN_EOF)) {
        if (match(TOKEN_FUNC)) skipFunctionDecl();
        else declaration(false, true);
    }
    
    endCompilation();
}