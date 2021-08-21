#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"
#include "assembler.h"

int main(int argc, char *argv[]) {
    int i;
    unsigned int ICF, DCF;
    SymbolTable *symbolTable;
    ParsedFile *file;
    char *filename, *ext;
    for (i = 1; i < argc; ++i) {
        filename = argv[i];
        ext = filename + strlen(filename) - 3;
        if (strcmp(ext, ".as") != 0){
            continue;
        }
        file = createParsedFile(filename);
        symbolTable = createSymbolTable();
        if (!first_pass(file, symbolTable, &ICF, &DCF)){
            return 0; /* errors in first pass */
        }
        if (!second_pass(file,symbolTable)){
            return 0; /* errors in second pass */
        }
        printFile(*file);
        printEntries(symbolTable);
        printExtern(*file);
    }
    return 0;
}









