//
// Created by orenb on 13/08/2021.
//

#ifndef ASSEMBLER_HW_LINEOFCODE_H
#define ASSEMBLER_HW_LINEOFCODE_H

#include "BinaryCommand.h"

typedef struct LineOfCode LineOfCode;
struct LineOfCode {
    char* source;
    BinaryCommand binaryCommand;
    int address;
    struct Token * tokens;
    int numOfTokens;
};
#endif //ASSEMBLER_HW_LINEOFCODE_H
