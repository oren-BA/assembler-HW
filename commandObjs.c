//
// Created by orenb on 13/08/2021.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"

#define TRUE 1
#define FALSE 0

int tokenCount(const char* sourceCode){
    int i = 0;
    int counter = 0;
    while (sourceCode[i] != '\n'){
        if(sourceCode[i] == ' ' || sourceCode[i] == ','){
            counter++;
        }
    }
    return counter;
}

char** splitLine(char* sourceCode, int wordNum){
    int end = 0;
    int start = 0;
    char** words = (char**)malloc(sizeof(char*) * wordNum);
    int wordIndex = 0;
    int wordLen;
    while (sourceCode[end] != '\n'){
        if (sourceCode[end] == ' ' || sourceCode[end] == ','){
            wordLen = end-start;
            words[wordIndex] = malloc(sizeof(char)*(wordLen+1)); //+1 for null terminator
            memcpy(words[wordIndex], sourceCode+start, wordLen );
            words[wordIndex][wordLen] = '\0';
            start = end+1;
            end++;
            wordIndex++;
        }
        end++;
    }
    // Handle last word
    wordLen = end-start;
    words[wordIndex] = malloc(sizeof(char)*(wordLen+1)); //+1 for null terminator
    memcpy(words[wordIndex], sourceCode+start, wordLen );
    words[wordIndex][wordLen] = '\0';
    return words;
}

int isCommandWord(char* word){
    char* commandWords[] = {"add", "sub"}; //TODO add all commands
    for (int i = 0; i < 2; ++i) { //TODO add correct num
        if (strcmp(word, commandWords[i]) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

int isNumber(const char* word){
    int i = 0;
    if (word[0] == '-'){
        i++;
    }
    while (word[i] != '\0'){
        if(word[i] < '0' || word[i] > '9'){
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

int isString(char* word){ //TODO check .asciz definition
    if (word[0] != '"'){
        return FALSE;
    }
    if (word[strlen(word)-1] != '"'){
        return FALSE;
    }
    for (int i = 1; i < strlen(word) - 1; ++i) {
        if (word[i] == '"'){
            return FALSE;
        }
    }
    return TRUE;
}

Token wordToToken(char* word){
    Token t;
    t.content = malloc(strlen(word));
    strcpy(t.content, word);
    if(word[0] == '$'){
        t.type = Register;
    } else if(isCommandWord(word)){
        t.type = Command;
    } else if (isNumber(word)){
        t.type = Number;
    } else if (isString(word)){
        t.type = String;
    } else if (word[strlen(word)-1] == ':'){
        t.type = LabelDefinition;
    }
    return t;
}

Token * tokenize(char* sourceCode){
    int tokenNum = tokenCount(sourceCode);
    char** words = splitLine(sourceCode, tokenNum);
    Token* tokens = (Token*)malloc(sizeof(Token)*tokenNum);
    for (int i = 0; i < tokenNum; ++i) {
        tokens[i] = wordToToken(words[i]);
    }
    return tokens;
}


BinaryCommand tokensToBinary(Token* tokens){
    BinaryCommand b;
    return b;
}

struct LineOfCode parseLine(char* sourceCode, int address){
    LineOfCode l;
    l.source = sourceCode;
    l.tokens = tokenize(sourceCode);
    l.address = address;
    l.binaryCommand = tokensToBinary(l.tokens);
    return l;
}


int main(int argc, char* argv[]){
    char** words = splitLine("MAIN: add $3,$5,$9\n",5);
    for (int i = 0; i < 5; ++i) {
        printf("%s ",words[i]);
    }
}









