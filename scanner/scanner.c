/********************scanner.c***********************/
/*  Předmět: IFJ - FIT VUT v Brně                   */
/*  implementace: Anastasiia Mironova (xmiron05)    */
/* **************************************************/

#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_PROGRAM_SIZE 128

/*
    Reads through all of standard input and outputs long string of input. 
    If gets allocation error, exits with 99 code.
*/
char* readFile() {
    char* program = malloc(sizeof(char) * INITIAL_PROGRAM_SIZE); //allocates initial memory for program text
    if (program == NULL) exit(99);

    size_t size = INITIAL_PROGRAM_SIZE;
    size_t index = 0;
    int ch;

    while ((ch = getchar()) != EOF) { //iterates over all of the stdandard input
        program[index++] = ch; //stores new char at index
        if (index == size - 1) { //resizes program if needed
            size *= 2;
            char* new_program = (char*) realloc(program, size);
            if (new_program == NULL) {
                free(program);
                exit(99);
            } 
            program = new_program;
        }
    }

    program[index] = '\0';

    return program;
}


TokenList* parseTokens() {
    char* program = readFile();

    initScanner();
    scanTokens();

    free(program);
    return NULL;
}