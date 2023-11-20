/*******************symtable_test.c******************/
/*  Předmět: IFJ - FIT VUT v Brně                   */
/*  implementace: Maksim Dubrovin (xdubro01)        */
/* **************************************************/

#include "unity.h"
#include "../data_structures/symtable.h"

void setUp(void) {
}

void tearDown(void) {
}




void test_insert_and_get_function(void) {
    symtable* table = symtable_create_table(FUNCTION_TABLE);
    char* key1 = "test_key1";
    char* key2 = "test_key2";
    char* key3 = "test_key3";

    symtable_insert_function(table, key1, NONE_TYPE, 1);
    symtable_insert_function(table, key2, INTEGER, 2);
    symtable_insert_function(table, key3, STRING, 3);

    funcInfo *info = symtable_get_pair(table, key1);
    TEST_ASSERT_TRUE(info->numOfParams == 1);
    TEST_ASSERT_TRUE(info->returnType == NONE_TYPE);

    info = symtable_get_pair(table, key2);
    TEST_ASSERT_TRUE(info->numOfParams == 2);
    TEST_ASSERT_TRUE(info->returnType == INTEGER);

    info = symtable_get_pair(table, key3);
    TEST_ASSERT_TRUE(info->numOfParams == 3);
    TEST_ASSERT_TRUE(info->returnType == STRING);
    symtable_delete_table(table);
}

void test_insert_and_get_variable(void) {
    symtable* table = symtable_create_table(FUNCTION_TABLE);
    char* key1 = "test_key1";
    char* key2 = "test_key2";
    char* key3 = "test_key3";

    symtable_insert_variable(table, key1, true, NONE_TYPE);
    symtable_insert_function(table, key2, false, INTEGER);
    symtable_insert_function(table, key3, false, STRING);

    varInfo *info = symtable_get_pair(table, key1);
    TEST_ASSERT_TRUE(info->isConst);
    TEST_ASSERT_TRUE(info->type == NONE_TYPE);

    info = symtable_get_pair(table, key2);
    TEST_ASSERT_TRUE(info->isConst == false);
    TEST_ASSERT_TRUE(info->type == INTEGER);

    info = symtable_get_pair(table, key3);
    TEST_ASSERT_TRUE(info->isConst == false);
    TEST_ASSERT_TRUE(info->type == STRING);
    symtable_delete_table(table);
}

void test_get_pair_not_found(void) {
    symtable* table = symtable_create_table(FUNCTION_TABLE);
    char* key = "non_existent_key";

    TEST_ASSERT_NULL(symtable_get_pair(table, key));

    symtable_delete_table(table);
}

void test_insert_and_delete_variable(void) {
    symtable* table = symtable_create_table(VARIABLE_TABLE);
    char* key1 = "key_to_delete1";
    char* key2 = "key_to_delete2";

    symtable_insert_variable(table, key1, true, NONE_TYPE);
    symtable_insert_function(table, key2, false, INTEGER);

    varInfo *info = symtable_get_pair(table, key1);
    TEST_ASSERT_TRUE(info->isConst);
    TEST_ASSERT_TRUE(info->type == NONE_TYPE);

    info = symtable_get_pair(table, key2);
    TEST_ASSERT_TRUE(info->isConst == false);
    TEST_ASSERT_TRUE(info->type == INTEGER);

    symtable_delete_pair(table, key1);

    TEST_ASSERT_NULL(symtable_get_pair(table, key1));
    TEST_ASSERT_NOT_NULL(symtable_get_pair(table, key2));

    symtable_delete_table(table);
}
//
//
//void test_insert_and_delete_and_find_pair(void) {
//    symtable* table = symtable_create_table();
//
//    for (int i = 0; i < 1000; i++) {
//        char key[20];
//        sprintf(key, "key%d", i);
//        char value[20];
//        sprintf(value, "value%d", i);
//        symtable_insert_pair(table, key, value);
//    }
//    //deletes every third pair
//    for (int i = 0; i < 1000; i++) {
//        if(i % 2 != 0) continue;
//        char key[20];
//        sprintf(key, "key%d", i);
//        symtable_delete_pair(table, key);
//        TEST_ASSERT_NULL(symtable_get_pair(table, key));
//    }
//
//    for (int i = 0; i < 1000; i++) {
//        char key[20];
//        sprintf(key, "key%d", i);
//        char value[20];
//        sprintf(value, "value%d", i);
//        if(i % 2 == 0)
//            TEST_ASSERT_NULL(symtable_get_pair(table, key));
//        else
//            TEST_ASSERT_EQUAL_STRING(value, symtable_get_pair(table, key));
//    }
//
//
//    symtable_delete_table(table);
//}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_insert_and_get_function);
    RUN_TEST(test_insert_and_get_variable);
    RUN_TEST(test_insert_and_delete_variable);
    return UNITY_END();
}