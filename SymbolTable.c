#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"
#include "SymbolTable.h"


void insertSymbol(SymbolTable* table, char* symbol, unsigned int value, int attributes) {

}


SymbolTable *createSymbolTable() {
    SymbolTable* result = malloc(sizeof(*result));
    result->entires = NULL;
    result->entries_num = 0;
    return result;
}

void destroySymbolTable(SymbolTable *table) {

}

void addAttribute(SymbolTable *table, struct Token token, enum SymbolAttribute attribute) {

}