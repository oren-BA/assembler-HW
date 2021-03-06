#ifndef ASSEMBLER_HW_TOKEN_H
#define ASSEMBLER_HW_TOKEN_H

#include <stdlib.h>
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

Token wordToToken(char*,int);
int isCommandWord(char* word);
int isString(char* word);




#endif /* ASSEMBLER_HW_TOKEN_H */
