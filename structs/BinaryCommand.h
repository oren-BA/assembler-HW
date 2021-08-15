#ifndef ASSEMBLER_HW_BINARYCOMMAND_H
#define ASSEMBLER_HW_BINARYCOMMAND_H
#include <stdio.h>

enum LineType{R, I, J, D, ASCII, E};

typedef struct BinaryCommand BinaryCommand;
struct  BinaryCommand{
    unsigned int size;
    char* payload;
    char* mask; /* indicates which bits are yet to be determined. 0 - not determined */
} ;

BinaryCommand *createBinary(size_t size, char* payload, char* mask);

#endif /* ASSEMBLER_HW_BINARYCOMMAND_H */
