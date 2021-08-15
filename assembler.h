#ifndef ASSEMBLER_HW_ASSEMBLER_H
#define ASSEMBLER_HW_ASSEMBLER_H

#include "SymbolTable.h"

int first_pass(ParsedFile* file, SymbolTable *symbol_table, unsigned int* ICF, unsigned int* DCF);
int second_pass(ParsedFile* file, SymbolTable *symbol_table);

#endif
