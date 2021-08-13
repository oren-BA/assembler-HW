
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"

/*
bool validate_line(LineOfCode line){
     TODO
}
*/

void createBinary(ParsedFile* file) {

}


int main(int argc, char* argv[]){
    char *sourceCode = "MAIN: add $3,$5,$9\n";
    char** words = splitLine(sourceCode, 5);
    Token* tokens = tokenize(sourceCode, 5);
    int i;
    for ( i = 0; i < argc; ++i) {
        char* filename = argv[i];
        ParsedFile *parsed_file = createParsedFile(filename);
        createBinary(parsed_file);
    }
    char test[3] = "$23";
    int num = strtol(test+1, NULL,10);
    printf("%d", num);
    return 0;
}









