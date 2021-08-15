
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


int main(int argc, char* argv[]){
//    split2("",0);
//    ParsedFile *file = createParsedFile("");
//    first_pass(file);
//    struct LineOfCode line = *createLine(".la $2");
//    validate_line(line);
//    split2("  MAIN:   .dh 6,7,  7 ,   ,,, ,s",10);
    printf("lines: %d",countLines("/Users/orenbenaltabe/CLionProjects/assembler-HW/structs/input.txt"));
//    printf("%d\n",1<<1);
//    char c[2];
//    c[0] = (char)(0xabcd & 0xff);
//    c[1] = (char)(0xabcd>>8 & 0xff);
//    printf("%x\n", c[0] & 0xff);
//    printf("%x\n", c[1] & 0xff);
//    printf("%x\n", c[2] & 0xff);
//    printf("%x\n", c[3] & 0xff);
//    char *sourceCode = ".extern x";
//    LineOfCode* line = createLine(sourceCode, 0);
//    int res = validate_line(*line);
    /*int res = validateRegister("$2");
    printf(sourceCode);
    printf("\nres: %d\n", res);
    char c = 0xff;
    printf("%x\n", c & 0xff);
    int i;
    for (i = 0; i < 8; i++) {
        printf("%x", c);
    }
    return 0;
    char *sourceCode = "MAIN: add $3,,$5,$9";
    char** words = splitLine(sourceCode, 5);
    Token* tokens = tokenize(sourceCode, 5);

    char test[80] = "a,b,c";
    const char delim[2] = ",";
    char *token = strtok(test, delim);

    for ( i = 0; i < argc; ++i) {
        char* filename = argv[i];
        ParsedFile *parsed_file = createParsedFile(filename);
        createBinary(parsed_file);
    }*/
    return 0;
}









