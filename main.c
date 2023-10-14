// #include "scanner/scanner.h"
#include <stdio.h>
#include "scanner/scanner.h"
#include "data_structures/tokens.h"


int main(void) {
    TokenList* tokens = parseTokens();

    if (tokens->tokens[0].type == TOKEN_STAR) {
        printf("THIS IS START OF SCANNER HERE IS FUCKING READY\n");
        printf("meow meow meow\n");
    }

    token_delete_tokens(tokens);
}