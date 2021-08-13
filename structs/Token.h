#ifndef ASSEMBLER_HW_TOKEN_H
#define ASSEMBLER_HW_TOKEN_H

#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "BinaryCommand.h"

enum TokenType{
    LabelDefinition,
    Label,
    Command,
    Register,
    Number,
    String
};

typedef struct Token Token;
struct Token{
    enum TokenType type;
    char* content;
} ;

Token wordToToken(char*);

bool isNumber(const char* word);



#endif /* ASSEMBLER_HW_TOKEN_H */
