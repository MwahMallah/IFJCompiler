#include "unity.h"
#include "../data_structures/tokens.h"
#include "../data_structures/tokenTypes.h"

void setUp() {
    // This function is called before each test case.
}

void tearDown() {
    // This function is called after each test case.
}

void test_create_new_token_list() {
    token_list* tokens = new_token_list();
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_INT(0, tokens->size);
    TEST_ASSERT_EQUAL_INT(MAX_CAPACITY, tokens->capacity);
    token_delete_tokens(tokens);
}

void test_add_and_get_tokens() {
    token_list* tokens = new_token_list();

    token_add(tokens, IDENTIFIER, "my_variable", NULL, 1);
    token_add(tokens, NUMBER, "42", NULL, 1);

    token* token1 = token_get(tokens, 0);
    token* token2 = token_get(tokens, 1);

    TEST_ASSERT_EQUAL_INT(IDENTIFIER, token1->type);
    TEST_ASSERT_EQUAL_STRING("my_variable", token1->lexeme);
    TEST_ASSERT_EQUAL_INT(1, token1->line);

    TEST_ASSERT_EQUAL_INT(NUMBER, token2->type);
    TEST_ASSERT_EQUAL_STRING("42", token2->lexeme);
    TEST_ASSERT_EQUAL_INT(1, token2->line);

    token_delete_tokens(tokens);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_create_new_token_list);
    RUN_TEST(test_add_and_get_tokens);

    return UNITY_END();
}
