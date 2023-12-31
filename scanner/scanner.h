/*******************scanner.h***********************/
/*  Předmět: IFJ - FIT VUT v Brně                  */
/*  implementace: Dubrovin Maksim (xdubro01)       */
/* *********************************************** */


#ifndef __scanner_h
#define __scanner_h

#include "../data_structures/tokens.h"

TokenList* scanTokens(char* program); //parses through standard input and outputs TokenList
char* readInput();

#endif