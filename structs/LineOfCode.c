
#include <malloc.h>
#include <memory.h>
#include "Token.h"
#include "LineOfCode.h"
#include "../utils/string_utils.h"

char** splitLine(char* sourceCode, int wordNum){
    char delimiters[2] = {' ', ','};
    char **words = split(sourceCode, wordNum, delimiters, 2);
    return words;
}

Token * tokenize(char* sourceCode, int tokenNum){
    char** words = splitLine(sourceCode, tokenNum);
    Token* tokens = (Token*)malloc(sizeof(Token)*tokenNum);
    int i;
    for (i = 0; i < tokenNum; ++i) {
        tokens[i] = wordToToken(words[i]);
    }
    return tokens;
}

int tokenCount(const char* sourceCode){
    int i = 0;
    int counter = 0;
    /* counter seperators */
    while (sourceCode[i] != '\n'){
        if(sourceCode[i] == ' ' || sourceCode[i] == ','){
            counter++;
        }
        i++;
    }
    return counter+1;
}

BinaryCommand tokensToBinary(Token* tokens){
    /* TODO  implement*/
    BinaryCommand* b = (BinaryCommand*)malloc(1);
    return *b;
}

LineOfCode* createLine(char* sourceCode, int address){
    LineOfCode *l = malloc(sizeof(l));
    l->source = sourceCode;
    l->tokens_num = tokenCount(sourceCode);
    l->tokens = tokenize(sourceCode, l->tokens_num);
    l->address = address;
    l->binary_command = tokensToBinary(l->tokens);
    return l;
}
