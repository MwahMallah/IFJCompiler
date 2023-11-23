#ifndef __compiler_h
#define __compiler_h

#include "../data_structures/tokens.h"
#include "../data_structures/symtable.h"

int compile(TokenList* list, symtable* varTable, symtable* funcTable);

#endif