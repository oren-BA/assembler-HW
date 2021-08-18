#ifndef ASSEMBLER_HW_LINEOFCODE_H
#define ASSEMBLER_HW_LINEOFCODE_H

#include "BinaryCommand.h"
#include "Token.h"

typedef struct LineOfCode LineOfCode;
struct LineOfCode {
    char* source;
    BinaryCommand* binary;
    int address;
    int line_no;
    int has_label;
    Token label;
    struct Token * tokens;
    int tokens_num;
    int using_extern;
    int is_empty_or_comment;
};

Token* tokenize(char* sourceCode, int tokenNum);

int isNumber(const char* word);
int validate_line(LineOfCode line);
LineOfCode *createLine(char *sourceCode, int line_number);
int validateRegister(char *text);


char** splitLine(char* sourceCode, int wordNum);
enum LineType getLineType(LineOfCode* code);
#endif /* ASSEMBLER_HW_LINEOFCODE_H */
