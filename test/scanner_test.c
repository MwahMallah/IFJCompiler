/********************scanner_test.c******************/
/*  Předmět: IFJ - FIT VUT v Brně                   */
/*  implementace: Maksim Dubrovin (xdubro01)        */
/* **************************************************/

#include "unity.h"
#include "../scanner/scanner.h" 
#include "../data_structures/tokens.h"

void setUp() {
    // This function is called before each test case.
}

void tearDown() {
    // This function is called after each test case.
}

void test_read_file() {
    TEST_ASSERT_EQUAL_STRING("aboba", readFile());
    TEST_ASSERT_EQUAL_STRING("Lorem ipsum\r\n dolor sit amet,", readFile());
}

void test_parse_tokens() {
    TokenList* list = parseTokens();
    Token token1 = token_get(list, 0);
    TEST_ASSERT_EQUAL_INT(TOKEN_NUMBER, token1.type);
}


int main() {
    UNITY_BEGIN();
    
    //RUN_TEST(test_read_file); success
    
    return UNITY_END();
}
