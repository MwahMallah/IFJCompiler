/********************tokens_test.c*******************/
/*  Předmět: IFJ - FIT VUT v Brně                   */
/*  implementace: Maksim Dubrovin (xdubro01)        */
/* **************************************************/


#include "unity.h"
#include "../data_structures/tokens.h"
#include "../data_structures/tokenTypes.h"
#include <stdio.h>

void setUp() {
    // This function is called before each test case.
}

void tearDown() {
    // This function is called after each test case.
}

void test_create_new_token_list() {
    TokenList* tokens = new_token_list();
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_INT(0, tokens->size);
    TEST_ASSERT_EQUAL_INT(MAX_CAPACITY, tokens->capacity);
    token_delete_tokens(tokens);
}

void test_add_and_get_tokens() {
    TokenList* tokens = new_token_list();

    token_add(tokens, TOKEN_IDENTIFIER, "my_variable", 10);
    token_add(tokens, TOKEN_NUMBER, "42", 2);

    Token token1 = token_get(tokens, 0);
    Token token2 = token_get(tokens, 1);

    TEST_ASSERT_EQUAL_INT(TOKEN_IDENTIFIER, token1.type);
    TEST_ASSERT_EQUAL_INT(10, token1.length);

    TEST_ASSERT_EQUAL_INT(TOKEN_NUMBER, token2.type);
    TEST_ASSERT_EQUAL_INT(2, token2.length);

    //token_delete_tokens(tokens);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_create_new_token_list);
    RUN_TEST(test_add_and_get_tokens);

    return UNITY_END();
}
