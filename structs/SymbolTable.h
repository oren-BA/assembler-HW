#ifndef ASSEMBLER_HW_SYMBOLTABLE_H
#define ASSEMBLER_HW_SYMBOLTABLE_H

#define LABEL_ALREADY_EXISTS_ERROR 10
#define NO_SUCH_SYMBOL_ERROR 11

enum SymbolAttribute{DATA=1<<0, CODE=1<<1, EXTERN=1<<2, ENTRY=1<<3};

typedef struct SymbolTable SymbolTable;
typedef struct SymbolTableEntry SymbolTableEntry;

struct SymbolTable {
    struct SymbolTableEntry * first;
    int entries_num;
};

struct SymbolTableEntry{
    char* symbol;
    unsigned int value;
    unsigned int attributes;
    SymbolTableEntry *next;
    SymbolTableEntry *prev;
};

void printEntries(SymbolTable *table);
SymbolTableEntry *getEntry(SymbolTable *pTable, char *symbol);
SymbolTableEntry* createSymbolTableEntry(char *symbol, unsigned int value, int attributes);
void destroySymbolTableEntry(SymbolTableEntry symbolTableEntry);


int insertSymbol(SymbolTable* table, char* symbol, unsigned int value, int attributes);
int addAttribute(SymbolTable *table, char *symbol, enum SymbolAttribute attribute);
SymbolTable* createSymbolTable();
void destroySymbolTable(SymbolTable table);


#endif
