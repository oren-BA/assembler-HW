
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"
#include "structs/ParsedFile.h"


void createBinary(ParsedFile* file) {

}


int main(int argc, char* argv[]){
    char *sourceCode = ".extern x";
    LineOfCode* line = createLine(sourceCode, 0);
    int res = validate_line(*line);
    /*int res = validateRegister("$2");*/
    printf(sourceCode);
    printf("\nres: %d\n", res);

    return 0;
}









