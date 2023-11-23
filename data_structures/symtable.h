#ifndef __symtable__h
#define __symtable__h

/********************symtable.h*********************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Dubrovin Maksim (xdubro01)       */
/* *********************************************** */

//https://github.com/jamesroutley/write-a-hash-table - sample for reading

/*
    our table of symbols will store strings as values for now, it will be changed to something more sophisticated like token structure or expression
*/

#include <stdbool.h>
#include "valueTypes.h"

#define INITIAL_SIZE 53
#define PROBING_INCREMENT 7
#define LOAD_FACTOR 0.75

typedef enum{
    FUNCTION_TABLE,
    VARIABLE_TABLE
} TableType;

// structure that represents every symbol in table
typedef struct {  
    char* key;
    void* value;
} symbol;


//symbol table itself, represented by hash table with Open addressing
typedef struct {
    TableType type;
    int size;
    int count;
    symbol** pairs;
} symtable;

typedef struct variableInfo{
    bool isConst;
    ValueType type;
} varInfo;

typedef struct functionInfo{
    ValueType returnType;
    int numOfParams;
} funcInfo;

/*
    Library API
*/

symtable* symtable_create_table(TableType type); //creates new symbol table
void symtable_delete_table(symtable* table); //deletes table itself
void symtable_insert_variable(symtable* table, char* key, bool isConst, ValueType type);
void symtable_insert_function(symtable* table, char* key, ValueType returnType, int numOfParams);
void *symtable_get_pair(symtable* table, char* key); //searches for  value by a given key
void symtable_delete_pair(symtable* table, char* key); //deletes entry with a given key

/**/

#endif