#ifndef ASSEMBLER_HW_BINARYCOMMAND_H
#define ASSEMBLER_HW_BINARYCOMMAND_H
#include <stdio.h>

enum LineType{R, I, J, D, ASCII, E, TypeError, EMPTY};

typedef struct BinaryCommand BinaryCommand;
struct  BinaryCommand{
    unsigned int size;
    char* payload;
} ;

BinaryCommand *createBinary(size_t size, char* payload);
void destroyBinary(BinaryCommand b);

#endif /* ASSEMBLER_HW_BINARYCOMMAND_H */
