#include <stdio.h>//????
#include <stdlib.h>
#include "symtable.h"
#include "stdint.h"
#include "str.h"

/********************symtable.C*********************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Ilya Volkov (xvolko02)         */
/* *********************************************** */

static void resize_table(symtable *table);
static symbol *create_symbol(char *key, char* value);
static symbol **init_pairs(int size);
static int get_hash_by_key(symtable *table, char *key);
static int get_addable_by_key(symtable *table, char *key);

static int hash_function(char *key, int tableSize);
static int rehash_function(int hash, int tableSize);

static void print_table(symtable *table);
static void error_search(symtable *table);

static int find_next_prime(int current);
static int is_prime(int n);

/*
    Creates new symbol table, sets size of symbol table to INITIAL_SIZE, count to zero. If memory wasn't allocated returns NULL.    
*/
symtable* symtable_create_table(){
    symtable *newTable = malloc(sizeof(symtable));
    if(newTable == NULL){
        return NULL;
        //todo errorcode
    }
    newTable->count = 0;
    newTable->size = INITIAL_SIZE;
    newTable->pairs = init_pairs(INITIAL_SIZE);
    return newTable;
}
/*
    Deallocates whole structure of symbol table.
*/
void symtable_delete_table(symtable* table) {
    for (int i = 0; i < table->size; ++i) {
        if(table->pairs[i] != NULL){
            free(table->pairs[i]->key);
            free(table->pairs[i]->value);
            free(table->pairs[i]);
        }
    }
    free(table->pairs);
    free(table);
    table = NULL;
}


/*
    Adds new entry of key-value pair to symbol table.
    Increases size, if needed.
    Increments count by one if operation succeeded.
*/
void symtable_insert_pair(symtable *table, char *key, char *value){
    if(table->count == table->size){
        resize_table(table);
    }
    int hashToAdd = get_hash_by_key(table, key);
    if(hashToAdd != -1){
        free(table->pairs[hashToAdd]->value);
        table->pairs[hashToAdd]->value = copy_string(value);
        return;
    }
    hashToAdd = get_addable_by_key(table, key);
    if(table->pairs[hashToAdd] != NULL){
        free(table->pairs[hashToAdd]);
    }
    table->pairs[hashToAdd] = create_symbol(key, value);
    table->count++;
}
/*
 * Returns:
 * Pointer to allocated block, which contains value of pair if found
 * NULL if pair wasn't found
 */
char *symtable_get_pair(symtable *table, char *key){
    int hashToFind = get_hash_by_key(table, key);
    if(hashToFind == -1) return NULL;
    return table->pairs[hashToFind]->value;
}
/*
    Deletes key-value pair from symbol table.
*/
void symtable_delete_pair(symtable *table, char *key){
    int hashToRemove = get_hash_by_key(table, key);
    if(hashToRemove == -1){
        return;
    }
    free(table->pairs[hashToRemove]->key);
    free(table->pairs[hashToRemove]->value);
    table->pairs[hashToRemove]->key = NULL;
    table->pairs[hashToRemove]->value = NULL;
    table->count--;
}



static void resize_table(symtable *table){
    int oldSize = table->size;
    int newSize = find_next_prime(oldSize * 2);
    symbol **tempPairs = table->pairs;
    table->pairs = init_pairs(newSize);
    table->size = newSize;
    table->count = 0;
    for (int i = 0; i < oldSize; ++i) {
        if(tempPairs[i] != NULL && tempPairs[i]->key != NULL){
            symtable_insert_pair(table, tempPairs[i]->key, tempPairs[i]->value);
        }
    }
    for (int i = 0; i < oldSize; ++i) {
        if(tempPairs[i] != NULL){
            free(tempPairs[i]->key);
            free(tempPairs[i]->value);
            free(tempPairs[i]);
        }
    }
    free(tempPairs);
}

static symbol **init_pairs(int size){
    symbol **new_pairs = malloc(sizeof(symbol*) * size);
    //checking if memory was allocated successfully
    if(new_pairs == NULL){
        exit(99);
    }
    for(int i = 0; i < size; ++i){
        new_pairs[i] = NULL;
    }
    return new_pairs;
}

static symbol *create_symbol(char *key, char* value){
    symbol *newPair = malloc(sizeof(symbol));
    newPair->key = copy_string(key);
    newPair->value = copy_string(value);
    return newPair;
}
/*
 * Returns:
 * -1 if table is full
 * hash if rehashing is completed
 */
static int hash_function(char *key, int tableSize){
//    unsigned int hash = 0;
//    int c;
//    while ((c = *key++)) {
//        hash = (hash * 31 + c);
//    }
//    hash = hash % tableSize;
//    return hash;
    uint32_t hash = 2166136261u;
    int c;
    while (c = *key++){
        hash ^= (uint8_t)c;
        hash *= 16777619;
    }
    return hash % tableSize;
}

static int rehash_function(int hash, int tableSize){
    int newHash = (hash + REHASH_INCREMENT) % tableSize;
    return newHash;
}
/*
 * Returns:
 * -1 if key wasn't found
 * hash of key if was found
 */
static int get_hash_by_key(symtable *table, char *key){
    int hash = hash_function(key, table->size);
    while(table->pairs[hash] != NULL){
        if(table->pairs[hash]->key != NULL){
            if(compare_strings(table->pairs[hash]->key, key) == 1)
                return hash;
        }
        hash = rehash_function(hash, table->size);
        //checking if whole table was searched
        if(hash == hash_function(key, table->size)) break;
    }
    return -1;
}
/*
 * Returns:
 * -1 if addable place wasn't found
 * hash of addable place if was found
 */
static int get_addable_by_key(symtable *table, char *key){
    int hash = hash_function(key, table->size);
    while(table->pairs[hash] != NULL && table->pairs[hash]->key != NULL){
        hash = rehash_function(hash, table->size);
        //checking if whole table wasn't searched
        if(hash == hash_function(key, table->size))
            return -1;
    }
    return hash;
}



static int is_prime(int n){
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6){
        if (n % i == 0 || n % (i + 2) == 0){
            return 0;
        }
    }
    return 1;
}

static int find_next_prime(int current){
    if (current < 2){
        return 2;
    }
    int next = current + 1;
    while (1){
        if (is_prime(next)){
            return next;
        }
        next++;
    }
}


// /*
//  * Creates pointer to block of allocated memory
//  * which contains copy of str string
//  */
// static char *copy_string(char *str){
//     int length = 0;
//     while(str[length] != '\0'){
//         length++;
//     }
//     char *newStr = malloc(sizeof(char) * (length + 1));
//     for(int i = 0; i < length; ++i){
//         newStr[i] = str[i];
//     }
//     newStr[length] = '\0';
//     return newStr;
// }//todo is public?
// /*
//  * Returns:
//  * 0 if unequal
//  * 1 if equal
//  */
// static int compare_strings(char *str1, char *str2){
//     while(*str1 && *str2){
//         if(*str1 != *str2) return 0;
//         str1++;
//         str2++;
//     }
//     if(*str1 == '\0' && *str2 == '\0'){
//         return 1;
//     }
//     return 0;
// }//todo is public?