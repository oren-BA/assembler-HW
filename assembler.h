#ifndef ASSEMBLER_HW_ASSEMBLER_H
#define ASSEMBLER_HW_ASSEMBLER_H

#include "SymbolTable.h"
void updateDataLinesAddress(ParsedFile *pFile, unsigned int i);
void updateDataSymbolsAddress(SymbolTable *table, unsigned int ICF);
int first_pass(ParsedFile* file, SymbolTable *symbol_table, unsigned int* ICF, unsigned int* DCF);
int second_pass(ParsedFile* file, SymbolTable *symbol_table);


#endif
