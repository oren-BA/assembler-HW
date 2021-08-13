
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

#include "Token.h"
#include "LineOfCode.h"

#define TRUE 1
#define FALSE 0
#define R_COMMANDS_NUM 8
#define I_COMMANDS_NUM 15
#define J_COMMANDS_NUM 4

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
    BinaryCommand* b = (BinaryCommand*)malloc(1);
    return *b;
}



bool validateLabelDef(char* w){
    /*TODO*/
}

enum CommandType getCommandType(char* cmd){
    /*TODO*/
    int i;
    char* rCommands[] = {"add", "sub", "and", "or", "nor", "move", "mhvi", "mvlo"};
    char* jCommands[] = {"jmp", "la", "call","stop"};
    for (i = 0; i < R_COMMANDS_NUM; ++i) {
        if (strcmp(cmd, rCommands[i]) == 0){
            return R;
        }
    }
    for (i = 0; i < J_COMMANDS_NUM; ++i) {
        if (strcmp(cmd, jCommands[i]) == 0){
            return J;
        }
    }
    return I;
}

int isNum(char c){
    if ((c >= '0' && c <= '9')) return TRUE;
    return FALSE;
}

int validateRegister(char* text){
    int len = strlen(text);
    if (len != 2 && len != 3) return FALSE;
    if (text[0] != '$') return FALSE;
    if (len == 2 && isNum(text[1]) == FALSE) return FALSE;
    if (len == 3 && isNum(text[1]) == FALSE && isNum(text[2]) == FALSE) return FALSE;
    int regNum = strtol(text+1, NULL,10);
    if (regNum>31) return FALSE;
    return TRUE;
}

int validateR(LineOfCode line){
    int i = 1;
    if (line.tokens[0].type == LabelDefinition){
        i = 2;
    }
    for (; i <line.tokens_num; ++i) { /*check if the last three tokens are valid registers*/
        if(line.tokens[i].type != Register || validateRegister(line.tokens[i].content) == FALSE) return FALSE;
    }
    return TRUE;
}

int validateI(LineOfCode line){
    /*TODO*/
}

int validateJ(LineOfCode line){
    /*TODO*/
}



int validate_line(LineOfCode line){
    int i = 0;
    if (line.tokens[i].type == LabelDefinition){
        if (validateLabelDef(line.tokens[i].content) == FALSE) return FALSE;
        i++;
    }
    if (isCommandWord(line.tokens[i].content) == TRUE){
        enum CommandType commandType = getCommandType(line.tokens[i].content);
        if (commandType == R){
            return validateR(line);
        } else if (commandType == I){
            return validateI(line);
        }
        return validateJ(line);
    }
    /*TODO add support for data instructions, e.g: .asciz*/

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



