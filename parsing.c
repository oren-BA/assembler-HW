//
// Created by orenb on 13/08/2021.
//
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
bool isNumber(const char* word){
    int i = 0;
    if (word[0] == '-'){
        i++;
    }
    while (word[i] != '\0'){
        if(word[i] < '0' || word[i] > '9'){
            return false;
        }
        i++;
    }
    return true;
}

bool isString(char* word){ //TODO check .asciz definition
    if (word[0] != '"'){
        return false;
    }
    if (word[strlen(word)-1] != '"'){
        return false;
    }
    for (int i = 1; i < strlen(word) - 1; ++i) {
        if (word[i] == '"'){
            return false;
        }
    }
    return true;
}

bool validateLabelDef(char* w){
    //TODO
}

enum CommandType getCommandType(char* cmd){
    //TODO
}

int validateR(LineOfCode line){
    //TODO
}

int validateI(LineOfCode line){
    //TODO
}

int validateJ(LineOfCode line){
    //TODO
}

bool validate_line(LineOfCode line){
    int i = 0;
    if (line.tokens[i].type == LabelDefinition){
        if (validateLabelDef(line.tokens[i].content) == FALSE) return FALSE;
        i++;
    }
    if (isCommandWord(line.tokens[i].content) == TRUE){
        enum CommandType commandType = getCommandType(line.tokens[i].content);
        if (commandType == R){
            return validateR(line);
        } else if (commandType == I){
            return validateI(line);
        }
        return validateJ(line);
    }
    //TODO add support for data instructions, e.g: .asciz

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
    return 0;
}









