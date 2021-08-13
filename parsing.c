#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"

int tokenCount(const char* sourceCode){
    int i = 0;
    int counter = 0;
    /* counter seperators */
    while (sourceCode[i] != '\n'){
        if(sourceCode[i] == ' ' || sourceCode[i] == ','){
            counter++;
        }
        i++;
    }
    return counter+1;
}

bool validate_line(LineOfCode line){
    /* TODO */
}

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
}









