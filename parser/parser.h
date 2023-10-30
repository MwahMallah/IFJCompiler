#ifndef __parser_h
#define __parser_h

#include "../data_structures/tokens.h"
#include "../data_structures/tokenTypes.h"
#include "../data_structures/symtable.h"

//parses entire program
void parse(TokenList* list, symtable* table);

#endif