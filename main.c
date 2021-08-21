
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"
#include "assembler.h"
#include "utils/string_utils.h"


int main(int argc, char *argv[]) {

    ParsedFile* file = createParsedFile("D:\\Repositories\\assembler-HW\\structs\\input.txt");
    unsigned int ICF, DCF;
    SymbolTable * symbolTable = createSymbolTable();
    first_pass(file, symbolTable, &ICF, &DCF);
    second_pass(file,symbolTable);
    printFile(*file);
    printEntries(symbolTable);
    printExtern(*file);
    return 0;
}









