
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
    char *sourceCode = "add $3,$1,$9";
    LineOfCode* line = createLine(sourceCode, 0);
    int res = validate_line(*line);
    /*int res = validateRegister("$2");*/
    printf("res: %d", res);
    return 0;
}









