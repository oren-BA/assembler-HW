#ifndef ASSEMBLER_HW_LINEOFCODE_H
#define ASSEMBLER_HW_LINEOFCODE_H

#include "BinaryCommand.h"
#include "Token.h"

typedef struct LineOfCode LineOfCode;
struct LineOfCode {
    char* source;
    BinaryCommand binary_command;
    int address;
    int has_label;
    Token label;
    struct Token * tokens;
    int tokens_num;
};

Token* tokenize(char* sourceCode, int tokenNum);

int isNumber(const char* word);
int validate_line(LineOfCode line);
LineOfCode *createLine(char *sourceCode, int address);
int validateRegister(char *text);


char** splitLine(char* sourceCode, int wordNum);
#endif /* ASSEMBLER_HW_LINEOFCODE_H */
