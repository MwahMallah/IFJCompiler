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




void test_insert_and_get_pair(void) {
    symtable* table = symtable_create_table();
    char* key1 = "test_key1";
    char* value1 = "test_value1";
    char* key2 = "test_key2";
    char* value2 = "test_value2";
    char* key3 = "test_key3";
    char* value3 = "test_value3";

    symtable_insert_pair(table, key1, value1);
    symtable_insert_pair(table, key2, value2);
    symtable_insert_pair(table, key3, value3);

    TEST_ASSERT_EQUAL_STRING(value1, symtable_get_pair(table, key1));
    TEST_ASSERT_EQUAL_STRING(value2, symtable_get_pair(table, key2));
    TEST_ASSERT_EQUAL_STRING(value3, symtable_get_pair(table, key3));

    symtable_delete_table(table);
}

void test_get_pair_not_found(void) {
    symtable* table = symtable_create_table();
    char* key = "non_existent_key";

    TEST_ASSERT_NULL(symtable_get_pair(table, key));

    symtable_delete_table(table);
}

void test_insert_and_delete_pair(void) {
    symtable* table = symtable_create_table();
    char* key1 = "key_to_delete1";
    char* value1 = "value_to_delete1";
    char* key2 = "key_to_delete2";
    char* value2 = "value_to_delete2";

    symtable_insert_pair(table, key1, value1);
    symtable_insert_pair(table, key2, value2);

    symtable_delete_pair(table, key1);

    TEST_ASSERT_NULL(symtable_get_pair(table, key1));
    TEST_ASSERT_EQUAL_STRING(value2, symtable_get_pair(table, key2));

    symtable_delete_table(table);
}

void test_insert_and_update_pair(void) {
    symtable* table = symtable_create_table();
    char* key = "key_to_update";
    char* value1 = "value_to_update1";
    char* value2 = "value_to_update2";

    symtable_insert_pair(table, key, value1);
    symtable_insert_pair(table, key, value2);

    TEST_ASSERT_EQUAL_STRING(value2, symtable_get_pair(table, key));

    symtable_delete_table(table);
}

void test_many_operations(void) {
    symtable* table = symtable_create_table();

    for (int i = 0; i < 200; i++) {
        char key[20];
        sprintf(key, "key%d", i);
        char value[20];
        sprintf(value, "value%d", i);
        symtable_insert_pair(table, key, value);
    }

    for (int i = 0; i < 200; i++) {
        char key[20];
        sprintf(key, "key%d", i);
        char value[20];
        sprintf(value, "value%d", i);
        TEST_ASSERT_EQUAL_STRING(value, symtable_get_pair(table, key));
    }


    for (int i = 0; i < 200; i++) {
        char key[20];
        sprintf(key, "key%d", i);
        symtable_delete_pair(table, key);
        TEST_ASSERT_NULL(symtable_get_pair(table, key));
    }

    symtable_delete_table(table);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_insert_and_get_pair);
    RUN_TEST(test_get_pair_not_found);
    RUN_TEST(test_insert_and_delete_pair);
    RUN_TEST(test_insert_and_update_pair);
    RUN_TEST(test_many_operations);
    return UNITY_END();
}


//void setUp() {
//    // This function is called before each test case.
//}
//
//void tearDown() {
//    // This function is called after each test case.
//}
//
//void test_create_new_symtable() {
//    symtable* table = symtable_create_table();
//    TEST_ASSERT_NOT_NULL(table);
//    // TEST_ASSERT_EQUAL_INT(0, table->count);
//    // TEST_ASSERT_EQUAL_INT(INITIAL_SIZE, table->size);
//    symtable_delete_table(table);
//}
//
//void test_add_and_find_symbol() {
//    symtable* table = symtable_create_table();
//    symtable_insert_pair(table, "key1", "value1");
//    symtable_insert_pair(table, "key2", "value2");
//
//    TEST_ASSERT_EQUAL_STRING("value1", symtable_get_pair(table, "key1"));
//    TEST_ASSERT_EQUAL_STRING("value2", symtable_get_pair(table, "key2"));
//
//
//    symtable_delete_table(table);
//}
//
//void test_add_and_delete_symbol() {
//    symtable* table = symtable_create_table();
//    symtable_insert_pair(table, "key1", "value1");
//    symtable_insert_pair(table, "key2", "value2");
//
//    symtable_delete_pair(table, "key1");
//
//    TEST_ASSERT_NULL(symtable_get_pair(table, "key1"));
//    TEST_ASSERT_EQUAL_STRING("value2", symtable_get_pair(table, "key2"));
//
//    symtable_delete_table(table);
//}
//
//void test_delete_entire_table() {
//    symtable* table = symtable_create_table();
//    symtable_insert_pair(table, "key1", "value1");
//    symtable_insert_pair(table, "key2", "value2");
//
//    symtable_delete_table(table);
//
//    TEST_ASSERT_NULL(table);
//    // TEST_ASSERT_EQUAL_INT(0, table->count);
//    // TEST_ASSERT_EQUAL_INT(0, table->size);
//    // TEST_ASSERT_EQUAL_PTR(NULL, symtable_find(table, "key1"));
//    // TEST_ASSERT_EQUAL_PTR(NULL, symtable_find(table, "key2"));
//}
//
//int main() {
//    UNITY_BEGIN();
//
//    RUN_TEST(test_create_new_symtable);
//    RUN_TEST(test_add_and_find_symbol);
//    RUN_TEST(test_add_and_delete_symbol);
//    RUN_TEST(test_delete_entire_table);
//
//    return UNITY_END();
//}
