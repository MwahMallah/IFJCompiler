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

#define INITIAL_SIZE 53
#define PROBING_INCREMENT 7
#define LOAD_FACTOR 0.75

// structure that represents every symbol in table
typedef struct {  
    char* key;
    char* value;
} symbol;


//symbol table itself, represented by hash table with Open addressing
typedef struct { 
    int size;
    int count;
    symbol** pairs;
} symtable;


typedef enum type{
    STRING_TYPE,
    INT_TYPE,
    DOUBLE_TYPE,
    VOID_TYPE
} dataType;

typedef union data{
    int intData;
    double doubleData;
    char *stringData;
} variableData;

typedef struct variableInfo{
    bool isConst;
    dataType type;
    char *name;
    variableData value;
} varInfo;

typedef struct functionInfo{
    dataType returnType;
    char *name;
    int numOfParams;
} funcInfo;

/*
    Library API
*/

symtable* symtable_create_table(); //creates new symbol table
void symtable_delete_table(symtable* table); //deletes table itself
void symtable_insert_pair(symtable* table, char* key, char* value);
char* symtable_get_pair(symtable* table, char* key); //searches for  value by a given key
void symtable_delete_pair(symtable* table, char* key); //deletes entry with a given key

/**/

#endif