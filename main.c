#include <stdio.h>
#include <stdlib.h>
#include "scanner/scanner.h"
#include "data_structures/tokens.h"
#include "test/debug.h"
#include "codeGenerator/compiler.h"
#include "data_structures/str.h"


int main(void) {
    char* program = readInput();
    TokenList* list = scanTokens(program);
    free(program);

    // for (int i = 0; i < list->size; i++) {
    //     printf("%3d, ", i + 1);
    //     printToken(list->tokens[i]);
    // }

    compile(list);

    token_delete_tokens(list);
}