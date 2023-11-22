#include <stdio.h>
#include <stdlib.h>
#include "scanner/scanner.h"
#include "test/debug.h"
#include "codeGenerator/compiler.h"
#include "parser/parser.h"
#include "data_structures/str.h"
#include "data_structures/tokens.h"
#include "data_structures/symtable.h"

int main(void) {
    char* program = readInput(4);
    TokenList* list = scanTokens(program);
    free(program);
    symtable* varTable = symtable_create_table(VARIABLE_TABLE);
    symtable* funcTable = symtable_create_table(FUNCTION_TABLE);

    // for (int i = 0; i < list->size; i++) {
    //     printf("%3d, ", i + 1);
    //     printToken(list->tokens[i]);
    // }

    // parse(list, varTable, funcTable);
    compile(list);

    token_delete_tokens(list);
}