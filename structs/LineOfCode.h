#ifndef ASSEMBLER_HW_LINEOFCODE_H
#define ASSEMBLER_HW_LINEOFCODE_H

#include "BinaryCommand.h"
#include "Token.h"

typedef struct LineOfCode LineOfCode;
struct LineOfCode {
    char* source;
    BinaryCommand binary_command;
    int address;
    struct Token * tokens;
    int tokens_num;
};

Token* tokenize(char* sourceCode, int tokenNum);

int isNumber(const char* word);


char** splitLine(char* sourceCode, int wordNum);
#endif /* ASSEMBLER_HW_LINEOFCODE_H */
