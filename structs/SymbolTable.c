#include "LineOfCode.h"
#include "ParsedFile.h"
#include "SymbolTable.h"
#include "../utils/string_utils.h"


#define FALSE 0
#define TRUE 1


SymbolTableEntry* createSymbolTableEntry(char *symbol, unsigned int value, int attributes) {
    SymbolTableEntry *entry = malloc(sizeof(*entry));
    entry->attributes = attributes;
    entry->value = value;
    entry->symbol = stringDuplicate(symbol);
    entry->next = NULL;
    entry->prev = NULL;
    return entry;
}

void destroySymbolTableEntry(SymbolTableEntry symbolTableEntry) {
    free(symbolTableEntry.symbol);
}

int insertSymbol(SymbolTable* table, char* symbol, unsigned int value, int attributes) {
    SymbolTableEntry *last;
    SymbolTableEntry *entry;
    char* dup_symbol = stringDuplicate(symbol);
    if (dup_symbol[strlen(dup_symbol)-1] == ':'){
        dup_symbol[strlen(dup_symbol)-1] = '\0';
    }
    if (getEntry(table, dup_symbol) != NULL){
        /*TODO add line number*/
        free(dup_symbol);
        return LABEL_ALREADY_EXISTS_ERROR;
    }
    entry = createSymbolTableEntry(dup_symbol, value, attributes);
    ++table->entries_num;
    if (table->first == NULL){
        table->first = entry;
        free(dup_symbol);
        return EXIT_SUCCESS;
    }
    last = table->first;
    while (last->next != NULL){
        last = last->next;
    }
    entry->prev=last;
    last->next = entry;
    free(dup_symbol);
    return EXIT_SUCCESS;
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

int addAttribute(SymbolTable *table, char* symbol, enum SymbolAttribute attribute) {
    SymbolTableEntry *entry = getEntry(table, symbol);
    if (entry == NULL){
        return NO_SUCH_SYMBOL_ERROR;
    }
    entry->attributes = entry->attributes | attribute;
    return EXIT_SUCCESS;
}

SymbolTableEntry *getEntry(SymbolTable *pTable, char *symbol) {
    SymbolTableEntry *entry = pTable->first;
    while (entry != NULL && strcmp(entry->symbol, symbol) != 0 ){
        entry = entry->next;
    }
    return entry;
}


void printEntries(SymbolTable *table) {
    SymbolTableEntry *entry = table->first;
    while (entry != NULL){
        if ((entry->attributes & ENTRY) != 0){
            printf("%s ", entry->symbol);
            printAddress(entry->value);
            printf("\n");
        }
        entry = entry->next;
    }
    printf("\n");
}