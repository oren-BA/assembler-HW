#ifndef ASSEMBLER_HW_SYMBOLTABLE_H
#define ASSEMBLER_HW_SYMBOLTABLE_H
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
SymbolTableEntry* createSymbolTableEntry(char *symbol, unsigned int value, int attributes);
void destroySymbolTableEntry(SymbolTableEntry symbolTableEntry);
SymbolTableEntry *getEntry(SymbolTable *pTable, char *symbol);

void insertSymbol(SymbolTable* table, char* symbol, unsigned int value, int attributes);
SymbolTable* createSymbolTable();
void destroySymbolTable(SymbolTable table);
void addAttribute(SymbolTable *table, char *symbol, enum SymbolAttribute attribute);


#endif
