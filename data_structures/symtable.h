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