#ifndef ASSEMBLER_HW_LINEOFCODE_H
#define ASSEMBLER_HW_LINEOFCODE_H

#include "BinaryCommand.h"

typedef struct LineOfCode LineOfCode;
struct LineOfCode {
    char* source;
    BinaryCommand binary_command;
    int address;
    struct Token * tokens;
    int tokens_num;
};

char** splitLine(char* sourceCode, int wordNum);
#endif /* ASSEMBLER_HW_LINEOFCODE_H */
