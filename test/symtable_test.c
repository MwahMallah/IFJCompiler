#include "unity.h"
#include "../data_structures/symtable.h" 

void setUp() {
    // This function is called before each test case.
}

void tearDown() {
    // This function is called after each test case.
}

void test_create_new_symtable() {
    symtable* table = new_symtable();
    TEST_ASSERT_NOT_NULL(table);
    // TEST_ASSERT_EQUAL_INT(0, table->count);
    // TEST_ASSERT_EQUAL_INT(INITIAL_SIZE, table->size);
    symtable_delete_table(table);
}

void test_add_and_find_symbol() {
    symtable* table = new_symtable();
    symtable_add(table, "key1", "value1");
    symtable_add(table, "key2", "value2");

    TEST_ASSERT_EQUAL_STRING("value1", symtable_find(table, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2", symtable_find(table, "key2"));

    symtable_delete_table(table);
}

void test_add_and_delete_symbol() {
    symtable* table = new_symtable();
    symtable_add(table, "key1", "value1");
    symtable_add(table, "key2", "value2");

    symtable_delete_pair(table, "key1");

    TEST_ASSERT_NULL(symtable_find(table, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2", symtable_find(table, "key2"));

    symtable_delete_table(table);
}

void test_delete_entire_table() {
    symtable* table = new_symtable();
    symtable_add(table, "key1", "value1");
    symtable_add(table, "key2", "value2");

    symtable_delete_table(table);

    TEST_ASSERT_NULL(table);
    // TEST_ASSERT_EQUAL_INT(0, table->count);
    // TEST_ASSERT_EQUAL_INT(0, table->size);
    // TEST_ASSERT_EQUAL_PTR(NULL, symtable_find(table, "key1"));
    // TEST_ASSERT_EQUAL_PTR(NULL, symtable_find(table, "key2"));
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_create_new_symtable);
    RUN_TEST(test_add_and_find_symbol);
    RUN_TEST(test_add_and_delete_symbol);
    RUN_TEST(test_delete_entire_table);
    
    return UNITY_END();
}
