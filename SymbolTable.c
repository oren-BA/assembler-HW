#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"
#include "SymbolTable.h"
#include "utils/string_utils.h"



SymbolTableEntry* createSymbolTableEntry(char *symbol, unsigned int value, int attributes) {
    SymbolTableEntry *entry = malloc(sizeof(*entry));
    entry->attributes = attributes;
    entry->value = value;
    entry->symbol = stringDuplicate(symbol);
    entry->next = NULL;
    entry->prev = NULL;
}

void destroySymbolTableEntry(SymbolTableEntry symbolTableEntry) {
    free(symbolTableEntry.symbol);
}

void insertSymbol(SymbolTable* table, char* symbol, unsigned int value, int attributes) {
    if (getEntry(table, symbol) != NULL){
        //TODO add line number
        printf("symbol \"%s\" already exists\n", symbol);
        return;
    }
    SymbolTableEntry *entry = createSymbolTableEntry(symbol, value, attributes);
    ++table->entries_num;
    if (table->first == NULL){
        table->first = entry;
        return;
    }
    SymbolTableEntry *last = table->first;
    while (last->next != NULL){
        last = last->next;
    }
    entry->prev=last;
    last->next = entry;
}


SymbolTable *createSymbolTable() {
    SymbolTable* result = malloc(sizeof(*result));
    result->first = NULL;
    result->entries_num = 0;
    return result;
}

void destroySymbolTable(SymbolTable table) {
    SymbolTableEntry *current;
    SymbolTableEntry *entry = table.first;
    while (entry != NULL){
        current = entry;
        entry = entry->next;
        destroySymbolTableEntry(*current);
        free(current);
    }
}

void addAttribute(SymbolTable *table, char* symbol, enum SymbolAttribute attribute) {
    SymbolTableEntry *entry = getEntry(table, symbol);
    if (entry == NULL){
        printf("no such symbol: \"%s\"\n", symbol);
        return;
    }
    entry->attributes = entry->attributes | attribute;
}

SymbolTableEntry *getEntry(SymbolTable *pTable, char *symbol) {
    SymbolTableEntry *entry = pTable->first;
    while (entry != NULL && strcmp(entry->symbol, symbol) != 0 ){
        entry = entry->next;
    }
    return entry;
}
