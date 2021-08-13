
#include <malloc.h>
#include <memory.h>
#include "Token.h"
#include "BinaryCommand.h"
#include "LineOfCode.h"

char** splitLine(char* sourceCode, int wordNum){
    int end = 0;
    int start = 0;
    char** words = (char**)malloc(sizeof(char*) * wordNum);
    int wordIndex = 0;
    int wordLen;
    while (sourceCode[end] != '\n'){
        /*TODO add support for consecutive whitespaces*/
        if (sourceCode[end] == ' ' || sourceCode[end] == ','){
            wordLen = end-start;
            /* +1 for null terminator */
            words[wordIndex] = malloc(sizeof(char)*(wordLen+1));
            memcpy(words[wordIndex], sourceCode+start, wordLen );
            words[wordIndex][wordLen] = '\0';
            start = end+1;
            end++;
            wordIndex++;
        }
        end++;
    }
    /* Handle last word */
    wordLen = end-start;
    words[wordIndex] = malloc(sizeof(char)*(wordLen+1)); /* +1 for null terminator */
    memcpy(words[wordIndex], sourceCode+start, wordLen );
    words[wordIndex][wordLen] = '\0';
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
    BinaryCommand b;
    return b;
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

