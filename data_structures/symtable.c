#include <stdio.h> //????
#include "symtable.h"

/********************symtable.C*********************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Ilya Volkov (YOUR LOGIN)         */
/* *********************************************** */


/*
    Creates new symbol table, sets size of symbol table to INITIAL_SIZE, count to zero. If memory wasn't allocated returns NULL.    
*/
symtable* new_symtable() {
    //TODO
    return NULL;
}

/*
    Adds new entry of key-value pair to symbol table.
    Increases size, if needed.
    Increments count by one if operation succeeded.
*/
void symtable_add(symtable* symbols, char* key, char* value) {
    //TODO

}

/*
    Searches for key in symbol table, if key if found returns value, otherwise returns NULL.
*/
char* symtable_find(symtable* symbols, char* key) {
    //TODO
    return NULL;
}


/*
    Deletes key-value pair from symbol table.
*/
void symtable_delete_pair(symtable* symbols, char* key) {
    //TODO
}

/*
    Deallocates whole structure of symbol table.
*/
void symtable_delete_table(symtable* symbols) {
    //TODO
}

