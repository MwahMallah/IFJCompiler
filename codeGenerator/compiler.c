#include <stdio.h>
#include <stdbool.h>
#include "compiler.h"
#include "../data_structures/str.h"
#include "../data_structures/valueTypes.h"
#include "../data_structures/symtable.h"
#include "../test/debug.h"

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

typedef ValueType (*ParseFn)(Token*, ValueType);

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
    ValueType type;
    bool isConst;
    bool isInitialized;
    bool isParam;
    int depth;
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
static symtable* varTable;
static symtable* funcTable;
static LocalList locals;
static int jumpNumber;
static int questionLabel;
static int substringLabel;

//function declarations
static void endCompilation();
static ValueType expression();
static void statement(bool isFirstFrame, Token* funcName);
static void declaration(bool isLocal, bool isFirstFrame, Token* funcName);
static ParseRule* getRule(TokenType type);
static ValueType parsePrecedence(Precedence precedence);
static ValueType variableDeclaration(bool isLocal, bool inFunctionParams);
static ValueType nativeType(char* funcName);
static bool isNative(char* funcName);
static bool isFunc(Token* funcName);

//pushes variable to list of local variables
static void pushLocal(Token* variable, bool isConst, bool isInitialized, bool isParam, ValueType declaredType) {
    Local newLocal;
    newLocal.variable = *variable;
    newLocal.depth = locals.scopeDepth;
    newLocal.type = declaredType;
    newLocal.isConst = isConst;
    newLocal.isInitialized = isInitialized;
    newLocal.isParam = isParam;
    locals.variables[++locals.localPos] = newLocal;
}

static bool localVarExistOnCurrentDepth(Token* variable) {
    for (int i = locals.localPos; locals.variables[i].depth == locals.scopeDepth; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return true;
        }
    }
    return false;
}

static bool globalVarExist(Token* variable) {
    varInfo* info = (varInfo*) symtable_get_pair(varTable, variable->lexeme);
    return info != NULL;
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

static bool localVarIsConst(Token* variable) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return locals.variables[i].isConst;
        }
    }
    return false;
}

static ValueType getLocalVarType(Token* variable) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return locals.variables[i].type;
        }
    }
    return NONE_TYPE;
}

static void initializeLocalVar(Token* variable) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            locals.variables[i].isInitialized = true;
            locals.variables[i].isParam = true;
        }
    }
}

static ValueType isLocalVarInitialized(Token* variable) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(variable->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return locals.variables[i].isInitialized;
        }
    }
    return false;
}

static void initializeVar(Token* variable) {
    if (variableIsLocal(variable)) {
        initializeLocalVar(variable);
    } else {
        varInfo* info = (varInfo*) symtable_get_pair(varTable, variable->lexeme);
        info->isInitialized = true;
    }
}

static bool varInitialized(Token* variable) {
    if (variableIsLocal(variable)) {
        return isLocalVarInitialized(variable);
    } else {
        varInfo* info = (varInfo*) symtable_get_pair(varTable, variable->lexeme);
        return info->isInitialized;
    }
}

static bool varExist(Token* variable) {
    if (variableIsLocal(variable)) {
        return true;
    } else {
        varInfo* info = (varInfo*) symtable_get_pair(varTable, variable->lexeme);
        return info != NULL;
    }
}

static bool checkUserFuncArgType(Token* funcName, ValueType argType, int paramNum) {
    funcInfo* info = (funcInfo*) symtable_get_pair(funcTable, funcName->lexeme);
    return argType == info->paramTypes[paramNum - 1];
}

static int getUserFuncArgumentPos(Token* prefix, Token* funcName) {
    if (prefix == NULL) return -1;
    funcInfo* info = (funcInfo*) symtable_get_pair(funcTable, funcName->lexeme);
    for (int i = 0; i < info->numOfParams; i++) {
        if (compare_strings(info->paramNames[i], prefix->lexeme) == 1) return i + 1;
    }
    return -1;
}

static int prefixedArgsInUserFunc(Token* funcName) {
    funcInfo* info = (funcInfo*) symtable_get_pair(funcTable, funcName->lexeme);
    int prefixedArgs = 0;
    for (int i = 0; i < info->numOfParams; i++) {
        if (compare_strings(info->paramNames[i], "_") == 0) prefixedArgs++;
    }
    return prefixedArgs;
}

static ValueType userFuncReturnType(Token* funcName) {
    funcInfo* info = (funcInfo*) symtable_get_pair(funcTable, funcName->lexeme);
    return info->returnType;
}

static bool isUserFunc(Token* funcName) {
    funcInfo* info = (funcInfo*) symtable_get_pair(funcTable, funcName->lexeme);
    return info != NULL;
}

static ValueType funcReturnType (Token* funcName) {
    if (isUserFunc(funcName)) return userFuncReturnType(funcName);
    else if (isNative(funcName->lexeme)) return nativeType(funcName->lexeme);
}

static ValueType variableType(Token* variable) {
    if (variableIsLocal(variable)) {
        return getLocalVarType(variable);
    } else {
        varInfo* info = (varInfo*) symtable_get_pair(varTable, variable->lexeme);
        return info == NULL? NONE_TYPE : info->type;
    }
}

static bool varIsConst(Token* variable) {
    if (variableIsLocal(variable)) {
        return localVarIsConst(variable);
    } else {
        varInfo* info = (varInfo*) symtable_get_pair(varTable, variable->lexeme);
        return info->isConst;
    }
}

static bool varIsParam(Token* var) {
    for (int i = locals.localPos; i >= 0; i--) {
        if (compare_strings(var->lexeme, locals.variables[i].variable.lexeme) == 1) {
            return locals.variables[i].isParam;
        }
    }
    
    return false;
}

static bool variableIsType(Token* variable, ValueType type) {
    return variableType(variable) == type;
}

static ValueType getValueType(Token* token) {
    switch (token->type)
    {
        case TOKEN_INTEGER:
            return INTEGER;
        case TOKEN_FLOAT:
            return FLOAT;    
        case TOKEN_STRING:
            return STRING;
        case TOKEN_IDENTIFIER:
            if (isFunc(token)) return funcReturnType(token);
            return variableType(token);
        case TOKEN_TYPE_STRING:
            return STRING;
        case TOKEN_TYPE_INT:
            return INTEGER;
        case TOKEN_TYPE_DOUBLE:
            return FLOAT;
        case TOKEN_TYPE_BOOLEAN:
            return BOOLEAN;
        default:
            return NONE_TYPE;
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

static bool isFunc(Token* funcName) {
    return isNative(funcName->lexeme) || isUserFunc(funcName);
}

static ValueType nativeFunc(char* funcName, int numArgs) {
    // printf("PUSHFRAME\n");
    if (compare_strings(funcName, "write") == 1) {
        for (int i = 1; i < numArgs; i++) {
            printf("WRITE LF@%%%d\n", i);
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
        printf("PUSHS LF@%%%d\n", 1);
        printf("INT2FLOATS\n");
        return FLOAT;
    } else if (compare_strings(funcName, "Double2Int")  == 1) {
        printf("FLOAT2INT GF@tmp_op1 LF@%%%d\n", 1);
        printf("PUSHS GF@tmp_op1\n");
        return INTEGER;
    } else if (compare_strings(funcName, "chr") == 1) {
        printf("PUSHS LF@%%%d\n", 1);
        printf("INT2CHARS\n");
        return STRING;
    } else if (compare_strings(funcName, "length") == 1) {
        printf("STRLEN GF@tmp_op1 LF@%%%d\n", 1);
        printf("PUSHS GF@tmp_op1\n");
        return INTEGER;
    } else if (compare_strings(funcName, "ord") == 1) {
        printf("PUSHS LF@%%%d\n", 1);
        printf("PUSHS int@0\n");
        printf("STRI2INTS\n");
        return INTEGER;
    } else if (compare_strings(funcName, "substring") == 1) {
        printf("LT GF@tmp_op1 LF@%%2 int@0\n");
        printf("JUMPIFEQ %%substringNil$%d GF@tmp_op1 bool@true\n", substringLabel);
        printf("LT GF@tmp_op1 LF@%%3 int@0\n");
        printf("JUMPIFEQ %%substringNil$%d GF@tmp_op1 bool@true\n", substringLabel);
        printf("JUMPIFEQ %%substringNil$%d LF@%%3 LF@%%2\n", substringLabel);
        printf("LT GF@tmp_op1 LF@%%3 LF@%%2\n");
        printf("JUMPIFEQ %%substringNil$%d GF@tmp_op1 bool@true\n", substringLabel);
        printf("STRLEN GF@tmp_op2 LF@%%1\n");     //length
        printf("GT GF@tmp_op1 LF@%%3 GF@tmp_op2\n");
        printf("JUMPIFEQ %%substringNil$%d GF@tmp_op1 bool@true\n", substringLabel);
        printf("STRLEN GF@tmp_op2 LF@%%1\n");     //length
        printf("JUMPIFEQ %%substringNil$%d GF@tmp_op2 LF@%%2\n", substringLabel);
        printf("GT GF@tmp_op1 LF@%%2 GF@tmp_op2\n");
        printf("JUMPIFEQ %%substringNil$%d GF@tmp_op1 bool@true\n", substringLabel);
        printf("PUSHS string@\n");
        printf("POPS GF@tmp_op1\n");   //accumulator
        printf("LABEL %%substring$%d\n", substringLabel);
        printf("PUSHS LF@%%2\n");
        printf("PUSHS LF@%%3\n");
        printf("JUMPIFEQS %%substringEnd$%d\n", substringLabel);
        printf("GETCHAR GF@tmp_op2 LF@%%1 LF@%%2\n");  //tmp_op2 = string[i]
        printf("CONCAT GF@tmp_op1 GF@tmp_op1 GF@tmp_op2\n");
        printf("ADD LF@%%2 LF@%%2 int@1\n");
        printf("JUMP %%substring$%d\n", substringLabel);
        printf("LABEL %%substringEnd$%d\n", substringLabel);
        printf("PUSHS GF@tmp_op1\n");
        printf("JUMP  %%substringEndFinal$%d\n", substringLabel);
        printf("LABEL %%substringNil$%d\n", substringLabel);
        printf("PUSHS nil@nil\n");
        printf("LABEL %%substringEndFinal$%d\n", substringLabel++);
        return STRING;
    }

    // printf("POPFRAME\n");
}

static ValueType nativeType(char* funcName) {
    if (compare_strings(funcName, "write") == 1) return NONE_TYPE;
    else if (compare_strings(funcName, "readInt") == 1) return INTEGER;
    else if (compare_strings(funcName, "readString") == 1) return STRING;
    else if (compare_strings(funcName, "readDouble") == 1) return FLOAT;
    else if (compare_strings(funcName, "Int2Double") == 1) return FLOAT;
    else if (compare_strings(funcName, "Double2Int")  == 1) return INTEGER;
    else if (compare_strings(funcName, "chr") == 1) return STRING;
    else if (compare_strings(funcName, "length") == 1) return INTEGER;
    else if (compare_strings(funcName, "ord") == 1) return INTEGER;
    else if (compare_strings(funcName, "substring") == 1) return STRING;   
}

static int nativeFuncParams(char* funcName) {
    if (compare_strings(funcName, "write") == 1) return 999;
    else if (compare_strings(funcName, "readInt") == 1) return 0;
    else if (compare_strings(funcName, "readString") == 1) return 0;
    else if (compare_strings(funcName, "readDouble") == 1) return 0;
    else if (compare_strings(funcName, "Int2Double") == 1) return 1;
    else if (compare_strings(funcName, "Double2Int")  == 1) return 1;
    else if (compare_strings(funcName, "chr") == 1) return 1;
    else if (compare_strings(funcName, "length") == 1) return 1;
    else if (compare_strings(funcName, "ord") == 1) return 1;
    else if (compare_strings(funcName, "substring") == 1) return 3;  
}


static bool checkNativeFuncArgType(char* funcName, ValueType argType, int paramNum) {
    if (paramNum > nativeFuncParams(funcName)) return false;
    
    if (compare_strings(funcName, "write") == 1) return true;
    else if (compare_strings(funcName, "readInt") == 1) return false;
    else if (compare_strings(funcName, "readString") == 1) return false;
    else if (compare_strings(funcName, "readDouble") == 1) return false;
    else if (compare_strings(funcName, "Int2Double") == 1) {
        return argType == INTEGER;
    }
    else if (compare_strings(funcName, "Double2Int")  == 1) {
        return argType == FLOAT;
    }
    else if (compare_strings(funcName, "chr") == 1) {
        return argType == INTEGER;
    }
    else if (compare_strings(funcName, "length") == 1) {
        return argType == STRING;
    }
    else if (compare_strings(funcName, "ord") == 1) {
        return argType == STRING;
    }
    else if (compare_strings(funcName, "substring") == 1) {
        if (paramNum == 1) {
            return argType == STRING;
        } else {
            return argType == INTEGER;
        }
    } 
    return false;
}

static int userFuncParams(char* funcName) {
    funcInfo* info = (funcInfo*) symtable_get_pair(funcTable, funcName);
    return info->numOfParams;
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

static void compilationError(int code) {
    endCompilation();
    printf("EXIT int@%d\n", code);
    exit(code);
}

static bool consume(TokenType type) {
    if (parser.current->type == type) {
        advance();
        return true;
    } else {
        compilationError(2);
    }
}

static bool checkNext(TokenType type) {
    Token* tok = parser.current + 1;
    return tok->type == type;
}


static bool check(TokenType type) {
    return parser.current->type == type;
}

static bool match(TokenType type) {
    if (!check(type)) return false;
    advance();
    return true;
}

static bool type(ValueType* declaredType, bool* nullable) {
    if (match(TOKEN_TYPE_DOUBLE)) {
        if (match(TOKEN_QUESTION)) *nullable = true;
        *declaredType = FLOAT;
        return true;
    } else if (match(TOKEN_TYPE_STRING)) {
        if (match(TOKEN_QUESTION)) *nullable = true;
        *declaredType = STRING;
        return true;
    } else if (match(TOKEN_TYPE_INT)) {
        if (match(TOKEN_QUESTION)) *nullable = true;
        *declaredType = INTEGER;
        return true;
    } else {
        compilationError(2);
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
static ValueType integer(Token* name, ValueType type) {
    if (getRule(name->type)->prefix != NULL && getRule(name->type)->infix == NULL) compilationError(2);
    printf("PUSHS int@%s\n", parser.previous->lexeme);
    return INTEGER;
}

//function, that adds push instruction to output file
//pushes float value to vm stack
static ValueType floating(Token* name, ValueType type) {
    if (getRule(name->type)->prefix != NULL && getRule(name->type)->infix == NULL) compilationError(2);
    // double value = strtodouble(parser.previous->lexeme);
    double value;
    sscanf(parser.previous->lexeme, "%lf", &value);

    printf("PUSHS float@%a\n", value);
    return FLOAT;
}

//parses literal expression
static ValueType literal(Token* name, ValueType type) {
    if (getRule(name->type)->prefix != NULL && getRule(name->type)->infix == NULL) compilationError(2);
    switch (parser.previous->type)
    {
        case TOKEN_TRUE: printf("PUSHS bool@%s\n", parser.previous->lexeme); break;
        case TOKEN_FALSE: printf("PUSHS bool@%s\n", parser.previous->lexeme); break;
        case TOKEN_NIL: {
            printf("PUSHS nil@%s\n", parser.previous->lexeme); 
            return NIL;
        }
        default: break;
    }
    
    return NONE_TYPE;
}

static ValueType string(Token* name, ValueType type) {
    if (getRule(name->type)->prefix != NULL && getRule(name->type)->infix == NULL) compilationError(2);
    printf("PUSHS string@%s\n", parser.previous->lexeme);
    return STRING;
}

static ValueType variable(Token* name, ValueType type) {
    if (getRule(name->type)->prefix != NULL && getRule(name->type)->infix == NULL) compilationError(2);

    Token* var = parser.previous;

    if (check(TOKEN_LEFT_PAREN)) return NONE_TYPE;
    printf("Locals depth: %d\n", locals.scopeDepth);
    printToken(locals.variables[locals.localPos].variable);
    if (!varExist(var)) compilationError(5);

    if (match(TOKEN_EQUAL)) {
        // if (varIsParam(var)) compilationError(9);
        if (varIsConst(var) && varInitialized(var)) compilationError(9);

        ValueType expressionType = expression();
        if (!variableIsType(var, expressionType)) compilationError(7);

        if (variableIsLocal(var)) {
            printf("POPS LF@%s$%d\n", var->lexeme, getVarDepth(var));
        } else {
            printf("POPS GF@%s\n", var->lexeme);
        }
        if (!varInitialized(var)) initializeVar(var);

    } else {
        if (!varInitialized(var)) compilationError(5);
        if (variableIsLocal(var)) {
            printf("PUSHS LF@%s$%d\n", var->lexeme, getVarDepth(var));
        } else {
            printf("PUSHS GF@%s\n", var->lexeme);
        }
        match(TOKEN_BANG);
    }

    return variableType(var);
}

static ValueType unary(Token* name, ValueType rType) {
    TokenType operator = parser.previous->type;
    Token* rightValue = parser.current;

    if (operator == TOKEN_MINUS) {
        if (rightValue->type == TOKEN_FLOAT || variableIsType(rightValue, FLOAT)) {
            printf("PUSHS float@0x0p+0\n");
        } else if (rightValue->type == TOKEN_INTEGER || variableIsType(rightValue, INTEGER)) {
            printf("PUSHS int@0\n");
        } else {
            compilationError(7);
        }
    }
    
    ValueType type = parsePrecedence(PREC_UNARY);
    printf("SUBS\n");
    return type;
}

//parses grouping expression
static ValueType grouping(Token* name, ValueType lType) {
    ValueType type = expression();
    consume(TOKEN_RIGHT_PAREN);
    return type;
}

//parses binary expression
static ValueType binary(Token* leftValue, ValueType leftValueType) {
    TokenType operator = parser.previous->type;
    Token* rightValue = parser.current;
    ParseRule* rule = getRule(operator);
    ValueType rightValueType = parsePrecedence((Precedence)(rule->precedence + 1));
    ValueType binaryOpType = NONE_TYPE;

    //implicitly cast integer to double
    if (leftValueType == FLOAT && rightValueType == INTEGER && (leftValue->type != TOKEN_IDENTIFIER || rightValue->type != TOKEN_IDENTIFIER)) {
        binaryOpType = FLOAT;
        printf("INT2FLOATS\n");
    } else if (leftValueType == INTEGER && rightValueType == FLOAT && (leftValue->type != TOKEN_IDENTIFIER || rightValue->type != TOKEN_IDENTIFIER)) {
        binaryOpType = FLOAT;
        printf("POPS GF@tmp_op1\n"); //right value
        printf("INT2FLOATS\n"); //left value to float
        printf("PUSHS GF@tmp_op1\n");
    } else if (leftValueType != rightValueType && leftValueType != NIL && rightValueType != NIL) {
        compilationError(7);
    }
    // if (getValueType(leftValue) == FLOAT && rightValueType == INTEGER) {
    //     binaryOpType = FLOAT;
    //     printf("INT2FLOATS\n");
    //     if (rightValue->type == TOKEN_INTEGER) rightValue->type = TOKEN_FLOAT;
    // } else if (getValueType(leftValue) == INTEGER && rightValueType == FLOAT) {
    //     binaryOpType = FLOAT;
    //     printf("POPS GF@tmp_op1\n"); //right value
    //     printf("INT2FLOATS\n"); //left value to float
    //     printf("PUSHS GF@tmp_op1\n");
    //     if (leftValue->type == TOKEN_INTEGER) leftValue->type = TOKEN_FLOAT;
    // } else if (leftValueType != rightValueType && ((leftValueType != INTEGER || leftValueType != FLOAT) && (rightValueType != FLOAT || rightValueType != INTEGER))) {
    //     compilationError(7);
    // }

    switch (operator)
    {
        case TOKEN_LESS: printf("LTS\n"); binaryOpType = BOOLEAN; break;
        case TOKEN_GREATER: printf("GTS\n"); binaryOpType = BOOLEAN; break;
        case TOKEN_EQUAL_EQUAL: printf("EQS\n"); binaryOpType = BOOLEAN; break;
        case TOKEN_BANG_EQUAL: printf("EQS\nNOTS\n"); binaryOpType = BOOLEAN; break;
        case TOKEN_LESS_EQUAL: printf("GTS\nNOTS\n"); binaryOpType = BOOLEAN; break;
        case TOKEN_GREATER_EQUAL: printf("LTS\nNOTS\n"); binaryOpType = BOOLEAN; break;
        case TOKEN_DOUBLE_QUESTIONS:
            printf("POPS GF@tmp_op2\n"); //right_operand
            printf("POPS GF@tmp_op1\n"); //left_operand
            printf("JUMPIFNEQ %%left_op$%d nil@nil GF@tmp_op1\n", questionLabel);   
            printf("PUSHS GF@tmp_op2\n");
            printf("JUMP %%right_op$%d\n", questionLabel);
            printf("LABEL %%left_op$%d\n", questionLabel);
            printf("PUSHS GF@tmp_op1\n");
            printf("LABEL %%right_op$%d\n", questionLabel++);
            if (leftValueType == STRING || rightValueType == STRING) binaryOpType = STRING;
            else if (leftValueType == INTEGER || rightValueType == INTEGER) binaryOpType = INTEGER;
            else if (leftValueType == FLOAT || rightValueType == FLOAT) binaryOpType = FLOAT;
            break;
        case TOKEN_PLUS: 
            if (getValueType(leftValue) == STRING || rightValueType == STRING) {
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

static ValueType call(Token* funcName, ValueType lType) {
    ValueType returnType = NONE_TYPE;
    int argumentNum = 1;
    int paramNum = 1;
    bool paramHasPrefix = false;
    printf("CREATEFRAME\n");
    if (isNative(funcName->lexeme)) {
        if (!check(TOKEN_RIGHT_PAREN)) {
            do {
                if (check(TOKEN_IDENTIFIER) && checkNext(TOKEN_COLON)) {
                    if (compare_strings(funcName->lexeme, "substring") == 0) compilationError(4);
                    match(TOKEN_IDENTIFIER);
                    Token* prefix = parser.previous;
                    if (argumentNum == 1) {
                        if (compare_strings(prefix->lexeme, "of") == 0) compilationError(4);
                    } else if (argumentNum == 2) {
                        if (compare_strings(prefix->lexeme, "startingAt") == 0) compilationError(4);
                    } else if (argumentNum == 3) {
                        if (compare_strings(prefix->lexeme, "endingBefore") == 0) compilationError(4);
                    }
                    match(TOKEN_COLON);
                }
                printf("DEFVAR TF@%%%d\n", argumentNum);
                ValueType argType = expression();
                if (!checkNativeFuncArgType(funcName->lexeme, argType, argumentNum)) compilationError(4);
                printf("POPS TF@%%%d\n", argumentNum++);
            } while (match(TOKEN_COMMA));
        }
        printf("PUSHFRAME\n");
        if (argumentNum - 1 > nativeFuncParams(funcName->lexeme)) compilationError(4);
        returnType = nativeFunc(funcName->lexeme, argumentNum);
        // printf("POPFRAME\n");
    } else if (isUserFunc(funcName)) {
        returnType = userFuncReturnType(funcName);

        if (!check(TOKEN_RIGHT_PAREN)) {
            Token* prefix = NULL;
            int prefixedArgs = 0;
            do {
                if (check(TOKEN_IDENTIFIER) && checkNext(TOKEN_COLON)) {
                    match(TOKEN_IDENTIFIER);
                    prefix = parser.previous;
                    match(TOKEN_COLON);
                    paramHasPrefix = true;
                }
                int prefixNum = getUserFuncArgumentPos(prefix, funcName);
                if (prefixNum < 0 && paramHasPrefix) compilationError(4);
                if (prefixNum > 0) {
                    paramNum = prefixNum;
                    prefixedArgs++;
                }
                printf("DEFVAR TF@%%%d\n", paramNum);
                if (match(TOKEN_COMMA)) compilationError(2);
                ValueType argType = expression();
                if (!checkUserFuncArgType(funcName, argType, paramNum)) compilationError(4);
                printf("POPS TF@%%%d\n", paramNum++);
                argumentNum++;
                paramHasPrefix = false;
            } while (match(TOKEN_COMMA));
            if (prefixedArgs != prefixedArgsInUserFunc(funcName)) compilationError(4);
        }
        printf("PUSHFRAME\n");

        if (argumentNum - 1 > userFuncParams(funcName->lexeme)) compilationError(4);
        printf("CALL $%s\n", funcName->lexeme);
        // printf("PUSHS TF@%%retval\n");
        if (userFuncReturnType(funcName) != NONE_TYPE) printf("PUSHS LF@%%retval\n");
    } else {
        compilationError(3);
    }

    printf("POPFRAME\n");
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
    [TOKEN_EOF] = {NULL, NULL, PREC_NONE},
    [TOKEN_RETURN] = {NULL,     NULL,   PREC_NONE},
    [TOKEN_VAR] = {NULL,     NULL,   PREC_NONE},
    [TOKEN_LET] = {NULL,     NULL,   PREC_NONE},
    [TOKEN_WHILE] = {NULL,     NULL,   PREC_NONE},
    [TOKEN_LEFT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_RIGHT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_FUNC] = {NULL,     NULL,   PREC_NONE},

};

//returns parsing rule for this operation
static ParseRule* getRule(TokenType type) {
    return &rules[type];
}

static ValueType parsePrecedence(Precedence precedence) {
    advance();

    //gets first token prefix rule and executes it
    ParseFn prefixOperation = getRule(parser.previous->type)->prefix;
    if (prefixOperation == NULL) compilationError(2);
    ValueType prefixType = prefixOperation(parser.current, NONE_TYPE);
    ValueType infixType = NONE_TYPE;
    Token* name;

    while (precedence <= getRule(parser.current->type)->precedence)
    {
        name = advance();
        ParseFn infixRule = getRule(parser.previous->type)->infix;
        infixType = infixRule(name, prefixType);
    }

    return infixType == NONE_TYPE? prefixType : infixType;
}

static ValueType expression() {
    return parsePrecedence(PREC_ASSIGNMENT);
}

static void block(Token* funcName) {
    while (!match(TOKEN_RIGHT_BRACE)) {
        declaration(true, false, funcName);
        if (check(TOKEN_EOF)) compilationError(2);
    }
}

static void funcDeclaration() {
    createLocalFrame();
    Token* funcName = parser.current;
    if (isFunc(funcName)) compilationError(3);
    char* prefixes[256];
    ValueType types[256];
    consume(TOKEN_IDENTIFIER);
    
    printf("LABEL $%s\n", funcName->lexeme);
    // printf("PUSHFRAME\n");
    printf("DEFVAR LF@%%retval\n");

    int argumentNum = 0;
    consume(TOKEN_LEFT_PAREN);
    if (!check(TOKEN_RIGHT_PAREN)) {
        do
        {
            Token* prefix = parser.current;
            consume(TOKEN_IDENTIFIER);
            Token* arg = parser.current; //current arg
            ValueType type = variableDeclaration(true, true);
            initializeLocalVar(arg);
            prefixes[argumentNum] = prefix->lexeme;
            types[argumentNum] = type;
            printf("MOVE LF@%s$%d LF@%%%d\n", arg->lexeme, getVarDepth(arg), ++argumentNum);
        } while(match(TOKEN_COMMA));
    }
    consume(TOKEN_RIGHT_PAREN);
    ValueType returnType = NONE_TYPE;
    if (match(TOKEN_ARROW)) {
        returnType = getValueType(parser.current);
        advance(); 
        match(TOKEN_QUESTION);
    } 
    symtable_insert_function(funcTable, funcName->lexeme, returnType, argumentNum, prefixes, types);
    match(TOKEN_EOL);
    consume(TOKEN_LEFT_BRACE);
    block(funcName);
    // printf("POPFRAME\n");
    printf("RETURN\n");
    popLocalFrame();
}

static ValueType variableDeclaration(bool isLocal, bool inFunctionParams) {
    bool isConst;
    bool isInitialized = false; 
    if (match(TOKEN_VAR)) isConst = false;
    else if (match(TOKEN_LET)) isConst = true;

    Token* var = parser.current;

    consume(TOKEN_IDENTIFIER); //check variable type next
    if (compare_strings(var->lexeme, "_") == 1) compilationError(2);

    if (isLocal) {
        if (localVarExistOnCurrentDepth(var)) compilationError(3);
        printf("DEFVAR LF@%s$%d\n", var->lexeme, locals.scopeDepth);
    } else {
        if (globalVarExist(var)) compilationError(3);
        printf("DEFVAR GF@%s\n", var->lexeme);
    }

    ValueType declaredType = NONE_TYPE;
    ValueType expressionType = NONE_TYPE;
    bool isNullable = false;

    if (match(TOKEN_COLON)) type(&declaredType, &isNullable);

    // if (!inFunctionParams) {
    if (match(TOKEN_EQUAL)) {
        isInitialized = true;
        expressionType = expression();
        if (expressionType == NONE_TYPE) compilationError(7);
        if (expressionType == FLOAT && declaredType == INTEGER) printf("FLOAT2INTS\n");
        else if (expressionType == INTEGER && declaredType == FLOAT) printf("INT2FLOATS\n");
        else if (expressionType == NIL && declaredType == NONE_TYPE) compilationError(8);
        else if (expressionType == NIL && !isNullable) compilationError(7);
        else if (expressionType == NIL && isNullable); 
        else if (expressionType != declaredType && declaredType != NONE_TYPE) compilationError(7);
    } else {
        printf("PUSHS nil@nil\n");     
    }

    if (expressionType == NONE_TYPE && declaredType == NONE_TYPE) compilationError(8);

    if (isLocal) {
        pushLocal(var, isConst, isInitialized, false , declaredType == NONE_TYPE? expressionType : declaredType);
        printf("POPS LF@%s$%d\n", var->lexeme, getVarDepth(var));
    } else {
        symtable_insert_variable(varTable, var->lexeme, isConst, isInitialized, false, declaredType == NONE_TYPE? expressionType : declaredType);
        printf("POPS GF@%s\n", var->lexeme);
    }

    if (check(TOKEN_EOF) || match(TOKEN_EOL));
    // }  
    return declaredType == NONE_TYPE? expressionType : declaredType;  
}

static void ifStatement(Token* funcName) {
    if (match(TOKEN_LET)) {
        printf("PUSHS nil@nil\n");
        Token* var = parser.current;
        advance();
        if (!varExist(var)) compilationError(5);
        if (variableIsLocal(var)) {
            printf("PUSHS LF@%s$%d\n", var->lexeme, getVarDepth(var));
        } else {
            printf("PUSHS GF@%s\n", var->lexeme);
        }        
    } else {
        bool hasPrefix = false;
        if (match(TOKEN_LEFT_PAREN)) hasPrefix = true;
        ValueType type = expression();
        if (type != BOOLEAN) compilationError(7);
        if (hasPrefix) consume(TOKEN_RIGHT_PAREN);
        printf("PUSHS bool@false\n"); //JUMPIFNEQS takes two values from stack, so we push one more
    }

    int ifStmtNum = jumpNumber++;

    printf("JUMPIFEQS elseJump%d\n", ifStmtNum); //escapes then statement

    match(TOKEN_EOL); //if there is EOL doesn't matter
    consume(TOKEN_LEFT_BRACE);
    createLocalFrame();
    block(funcName);
    match(TOKEN_EOL);
    popLocalFrame();
    printf("JUMP thenJump%d\n", ifStmtNum); //escapes else statement

    printf("LABEL elseJump%d\n", ifStmtNum); //label to jump to
    if (match(TOKEN_ELSE)) {
        match(TOKEN_EOL); //if here is EOL doesn't matter
        consume(TOKEN_LEFT_BRACE);
        createLocalFrame();
        block(funcName);
        match(TOKEN_EOL);
        popLocalFrame();
    }
    printf("LABEL thenJump%d\n", ifStmtNum);
}

static void returnStatement(Token* funcName) {
    if (!funcName) compilationError(2);
    ValueType returnType = userFuncReturnType(funcName);
    if (match(TOKEN_EOL)) {
        if (returnType != NONE_TYPE) compilationError(6);
        printf("PUSHS nil@nil\n");
        printf("POPS LF@%%retval\n");
    } else {
        ValueType exprType = expression();
        if (returnType == NONE_TYPE) compilationError(6);
        if (exprType != returnType) compilationError(4);
        printf("POPS LF@%%retval\n");
    }
    printf("RETURN\n");
}

static void whileStatement(Token* funcName) {
    int whileStmtNumber = jumpNumber++;
    bool hasPrefix = false;
    if (match(TOKEN_LEFT_PAREN)) hasPrefix = true;
    printf("LABEL whileStart%d\n", whileStmtNumber);
    expression();
    if (hasPrefix) consume(TOKEN_RIGHT_PAREN);
    printf("PUSHS bool@false\n");

    printf("JUMPIFEQS whileEnd%d\n", whileStmtNumber); //escapes then statement

    match(TOKEN_EOL); //if here is EOL doesn't matter
    consume(TOKEN_LEFT_BRACE);
    createLocalFrame();
    block(funcName);
    popLocalFrame();
    printf("JUMP whileStart%d\n", whileStmtNumber); //escapes else statement

    printf("LABEL whileEnd%d\n", whileStmtNumber); //label to jump to
}

static void expressionStatement() {
    expression();
    if (check(TOKEN_EOF) || match(TOKEN_EOL));
}

static void declaration(bool isLocal, bool isFirstFrame, Token* funcName) {
    if (check(TOKEN_VAR) || check(TOKEN_LET)) {
        variableDeclaration(isLocal, false);
    } else if (match(TOKEN_EOL)) {
    } else {
        statement(isFirstFrame, funcName);
    }
}

static void statement(bool isFirstFrame, Token* funcName) {
    if (match(TOKEN_IF)) {
        if (isFirstFrame) printf("CREATEFRAME\nPUSHFRAME\n");
        ifStatement(funcName);
        if (isFirstFrame) printf("POPFRAME\n");
    } else if (match(TOKEN_RETURN)) {
        returnStatement(funcName);
    } else if (match(TOKEN_WHILE)) {
        if (isFirstFrame) printf("CREATEFRAME\nPUSHFRAME\n");
        whileStatement(funcName);
        if (isFirstFrame) printf("POPFRAME\n");
    } else if (match(TOKEN_LEFT_BRACE)) {
        createLocalFrame();
        block(funcName);
        popLocalFrame();
    } else {
        expressionStatement();
    }
}

//initialises parser to first token in the list, writes header to output file
static void initCompiler(TokenList* userList, symtable* variables, symtable* functions) {
    parser.previous = userList->tokens;
    parser.current = userList->tokens;
    list = userList;
    varTable = variables;
    funcTable = functions;
    locals.localPos = -1;
    locals.scopeDepth = 0;
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
    symtable_delete_table(varTable);
    symtable_delete_table(funcTable);    
    token_delete_tokens(list);
}

//public function for compiling list of tokens
int compile(TokenList* list, symtable* variables, symtable* functions) {
    initCompiler(list, variables, functions);

    while (!match(TOKEN_EOF)) {
        if (match(TOKEN_FUNC)) funcDeclaration();
        else advance();
    }

    restartCompiler(list);

    printf("LABEL $$main\n");
    // advance();
    int i = 0;
    while (!match(TOKEN_EOF)) {
        if (match(TOKEN_FUNC)) skipFunctionDecl();
        else declaration(false, true, NULL);
    }
    
    endCompilation();
}