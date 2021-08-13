//
// Created by orenb on 13/08/2021.
//

#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"

#define NULL 0


BinaryCommand tokensToBinary(Token* tokens){
    BinaryCommand b;
    return b;
}

struct LineOfCode parseLine(char* sourceCode, int address){
    LineOfCode l;
    l.source = sourceCode;
    l.tokens = tokenize(sourceCode);
    l.address = address;
    l.binaryCommand = tokensToBinary(l.tokens);
    return l;
}


int main(int argc, char* argv[]){
    LineOfCode l = parseLine("hello", 100);
}









