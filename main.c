#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"
#include "assembler.h"

int main(int argc, char *argv[]) {
    int i;
    unsigned int ICF, DCF;
    FILE * fp;
    SymbolTable *symbolTable;
    ParsedFile *file;
    char *filename, *ext, *output_file;
    unsigned int name_size;
    for (i = 1; i < argc; ++i) {
        filename = argv[i];
        name_size = strlen(filename) - 3;
        ext = filename + name_size;
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

        output_file = malloc(name_size + 5);
        memcpy(output_file, filename, name_size + 1); /* +1 to include the '.' */
        output_file[name_size + 1] = 'o';
        output_file[name_size + 2] = 'b';
        output_file[name_size + 3] = '\0';
        fp = fopen (output_file, "w+");
        printFile(*file, fp);

        output_file[name_size + 1] = 'e';
        output_file[name_size + 2] = 'x';
        output_file[name_size + 3] = 't';
        output_file[name_size + 4] = '\0';
        fp = fopen (output_file, "w+");
        printEntries(symbolTable, fp);

        output_file[name_size + 1] = 'e';
        output_file[name_size + 2] = 'n';
        output_file[name_size + 3] = 't';
        output_file[name_size + 4] = '\0';
        fp = fopen (output_file, "w+");
        printExtern(*file, fp);

        free(output_file);
        destroySymbolTable(*symbolTable);
        free(symbolTable);
        destroyParsedFile(*file);
        free(file);
    }
    return 0;
}









