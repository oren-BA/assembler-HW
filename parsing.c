
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
    char *sourceCode = "main: .entry";
    LineOfCode* line = createLine(sourceCode, 0);
    int res = validate_line(*line);
    /*int res = validateRegister("$2");*/
    printf("res: %d\n", res);
    printf("check: %d", strtol("-50",NULL,10));

    return 0;
}









