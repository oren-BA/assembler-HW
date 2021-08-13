//
// Created by orenb on 13/08/2021.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs/BinaryCommand.h"
#include "structs/Token.h"
#include "structs/LineOfCode.h"

int tokenCount(const char* sourceCode){
    int i = 0;
    int counter = 0;
    // counter seperators
    while (sourceCode[i] != '\n'){
        if(sourceCode[i] == ' ' || sourceCode[i] == ','){
            counter++;
        }
        i++;
    }
    return counter+1;
}

char** splitLine(char* sourceCode, int wordNum){
    int end = 0;
    int start = 0;
    char** words = (char**)malloc(sizeof(char*) * wordNum);
    int wordIndex = 0;
    int wordLen;
    while (sourceCode[end] != '\n'){
        //TODO add support for consecutive whitespaces
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

bool isCommandWord(char* word){
    char* commandWords[] = {"add", "sub"}; //TODO add all commands
    for (int i = 0; i < 2; ++i) { //TODO add correct num
        if (strcmp(word, commandWords[i]) == 0){
            return true;
        }
    }
    return false;
}

bool isNumber(const char* word){
    int i = 0;
    if (word[0] == '-'){
        i++;
    }
    while (word[i] != '\0'){
        if(word[i] < '0' || word[i] > '9'){
            return false;
        }
        i++;
    }
    return true;
}

bool isString(char* word){ //TODO check .asciz definition
    if (word[0] != '"'){
        return false;
    }
    if (word[strlen(word)-1] != '"'){
        return false;
    }
    for (int i = 1; i < strlen(word) - 1; ++i) {
        if (word[i] == '"'){
            return false;
        }
    }
    return true;
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

Token * tokenize(char* sourceCode, int tokenNum){
    char** words = splitLine(sourceCode, tokenNum);
    Token* tokens = (Token*)malloc(sizeof(Token)*tokenNum);
    for (int i = 0; i < tokenNum; ++i) {
        tokens[i] = wordToToken(words[i]);
    }
    return tokens;
}


BinaryCommand tokensToBinary(Token* tokens){
    //TODO implement
    BinaryCommand b;
    return b;
}

struct LineOfCode parseLine(char* sourceCode, int address){
    LineOfCode l;
    l.source = sourceCode;
    l.numOfTokens = tokenCount(sourceCode);
    l.tokens = tokenize(sourceCode, l.numOfTokens);
    int count = 0;
    l.address = address;
    l.binaryCommand = tokensToBinary(l.tokens);
    return l;
}

LineOfCode* parseFile(char* filename) {
    //TODO
}

bool validate_line(LineOfCode line){
    //TODO
}

int main(int argc, char* argv[]){
    char *sourceCode = "MAIN: add $3,$5,$9\n";
    char** words = splitLine(sourceCode, 5);
    Token* tokens = tokenize(sourceCode, 5);
}









