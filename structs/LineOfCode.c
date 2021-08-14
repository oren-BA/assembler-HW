
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>


#include "Token.h"
#include "LineOfCode.h"

#define TRUE 1
#define FALSE 0
#define R_COMMANDS_NUM 8
#define I_COMMANDS_NUM 15
#define J_COMMANDS_NUM 4
#define D_COMMANDS_NUM 3
#define E_COMMANDS_NUM 2

#include "../utils/string_utils.h"

char **splitLine(char *sourceCode, int wordNum) {
    char delimiters[2] = {' ', ','};
    char **words = split(sourceCode, wordNum, delimiters, 2);
    return words;
}

Token *tokenize(char *sourceCode, int tokenNum) {
    char **words = splitLine(sourceCode, tokenNum);
    Token *tokens = (Token *) malloc(sizeof(Token) * tokenNum);
    int i;
    for (i = 0; i < tokenNum; ++i) {
        tokens[i] = wordToToken(words[i]);
    }
    return tokens;
}

int tokenCount(const char *sourceCode) {
    int i = 0;
    int counter = 0;
    /* counter seperators */
    while (sourceCode[i] != '\0') {
        if (sourceCode[i] == ' ' || sourceCode[i] == ',') {
            counter++;
        }
        i++;
    }
    return counter + 1;
}

BinaryCommand tokensToBinary(Token *tokens) {
    /* TODO  implement*/
    BinaryCommand *b = (BinaryCommand *) malloc(1);
    return *b;
}


int validateLabelDef(char *w) {
    /*TODO*/
    return TRUE;
}

enum CommandType getCommandType(char *cmd) {
    /*TODO add all command types*/
    int i;
    char *r_commands[] = {"add", "sub", "and", "or", "nor", "move", "mhvi", "mvlo"};
    char *j_commands[] = {"jmp", "la", "call", "stop"};
    char *d_commands[] = {".db", ".dw", ".dh"};
    char *e_commands[] = {".entry", ".extern"};
    if (strcmp(cmd, ".asciz") == 0) return ASCII;
    for (i = 0; i < R_COMMANDS_NUM; ++i) {
        if (strcmp(cmd, r_commands[i]) == 0) {
            return R;
        }
    }
    for (i = 0; i < J_COMMANDS_NUM; ++i) {
        if (strcmp(cmd, j_commands[i]) == 0) {
            return J;
        }
    }
    for (i = 0; i < D_COMMANDS_NUM; ++i) {
        if (strcmp(cmd, d_commands[i]) == 0) {
            return D;
        }
    }
    for (i = 0; i < E_COMMANDS_NUM; ++i) {
        if (strcmp(cmd, e_commands[i]) == 0) {
            return E;
        }
    }
    return I;
}

int isDigit(char c) {
    if ((c >= '0' && c <= '9')) return TRUE;
    return FALSE;
}

int validateTypeOrder(Token *tokens, int token_num, const enum TokenType *types, int types_num) {
    int i;
    if (token_num != types_num) return FALSE;
    for (i = 0; i < token_num; i++) {
        if (tokens[i].type != types[i]) return FALSE;
    }
    return TRUE;
}

int validateRegister(char *text) {
    int regNum;
    int len = strlen(text);
    if (len != 2 && len != 3) return FALSE;
    if (text[0] != '$') return FALSE;
    if (len == 2 && isDigit(text[1]) == FALSE) return FALSE;
    if (len == 3 && (isDigit(text[1]) == FALSE || isDigit(text[2]) == FALSE)) return FALSE;
    regNum = strtol(text + 1, NULL, 10);
    if (regNum > 31) return FALSE;
    return TRUE;
}

int validateToken(Token t) {
    if (strlen(t.content) == 0) return FALSE;
    if (t.type == Register) return validateRegister(t.content);
    if (t.type == LabelDefinition) return validateLabelDef(t.content);
    return TRUE;
}

int validateR(LineOfCode line) {
    enum TokenType types[4] = {Command, Register, Register, Register};
    if (line.tokens_num != 4) return FALSE; /*checks if line has 4 tokens */
    if (validateTypeOrder(line.tokens, line.tokens_num, types, 4) == TRUE) return TRUE;
    return FALSE;
}

int isConditionBranch(const char *cmd) {
    int i;
    char *commands[] = {"beq", "bne", "blt", "bgt"};
    for (i = 0; i < 4; ++i) {
        if (strcmp(cmd,commands[i]) == 0) return TRUE;
    }
    return FALSE;

}


int validateI(LineOfCode line) {
    /*TODO*/
    Token *tokens = line.tokens;
    enum TokenType types[4] = {Command, Register, Register, Label};
    enum TokenType types2[4] = {Command, Register, Number, Register};
    if (line.tokens_num != 4) return FALSE; /*checks if line has 4 tokens*/
    /*checks if command is in the condition branch format which is: cmd, reg, reg, label*/
    if (isConditionBranch(tokens[0].content) == TRUE) {
        if (validateTypeOrder(tokens, line.tokens_num, types, 4)) return TRUE;
    } else {     /*checks if command is in the other format which is: cmd, reg, num, reg*/
        if (validateTypeOrder(tokens, line.tokens_num, types2, 4)) {
            return TRUE;
        }
    }
    return FALSE;
}

int validateJ(LineOfCode line) {
    Token *tokens = line.tokens;
    if (strcmp(tokens[0].content,"stop") == 0){
        if (line.tokens_num == 1) return TRUE;
        return FALSE;
    }
    if (line.tokens_num != 2) return FALSE;
    if (tokens[1].type == Label) return TRUE;
    if (strcmp(tokens[0].content,"jmp") == 0 && tokens[1].type == Register){
        return TRUE;
    }
    return FALSE;
}

int getMaxSize(char* wordType){
    if (strcmp(wordType, ".db") == 0){
        return pow(2,7) - 1;
    }
    if (strcmp(wordType, ".dh") == 0){
        return pow(2,15) - 1;
    }
    if (strcmp(wordType, ".dw") == 0){
        return pow(2,31) - 1;
    }
}

int validateD(LineOfCode line){
    int i;
    int num;
    Token *tokens = line.tokens;
    if (line.tokens_num < 2) return FALSE;
    int maxNum = getMaxSize(tokens[0].content);
    for (i = 1; i < line.tokens_num; ++i) {
        if (tokens[i].type != Number) return FALSE;
        num = strtol(tokens[i].content,NULL,10);
        if (num < -(maxNum+1) || num > maxNum) return FALSE;
    }
    return TRUE;
}

int validateE(LineOfCode line){
    Token *tokens = line.tokens;
    if (line.tokens_num != 2) return FALSE;
    if (line.tokens[1].type != Label) return FALSE;
    return TRUE;
}

int validateAscii(LineOfCode line){
    Token *tokens = line.tokens;
    if (line.tokens_num != 2) return FALSE;
    if (line.tokens[1].type != String) return FALSE;
    return TRUE;
}

int validate_line(LineOfCode line) {
    int i;
    if (line.has_label) {
        if (validateToken(line.label) == FALSE) return FALSE;
    }
    for (i = 0; i < line.tokens_num; ++i) {
        if (validateToken(line.tokens[i]) == FALSE) return FALSE;
    }
    enum CommandType commandType = getCommandType(line.tokens[0].content);
    if (commandType == R) {
        return validateR(line);
    } else if (commandType == I) {
        return validateI(line);
    } else if (commandType == J) {
        return validateJ(line);
    }  else if (commandType == D) {
        return validateD(line);
    } else if (commandType == E) {
        return validateE(line);
    } else if (commandType == ASCII) {
        return validateAscii(line);
    }
    /*TODO add support for data instructions, e.g: .asciz*/

}

LineOfCode *createLine(char *sourceCode, int address) {
    LineOfCode *l = malloc(sizeof(*l));
    l->source = sourceCode;
    l->tokens_num = tokenCount(sourceCode);
    l->has_label = FALSE;
    l->tokens = tokenize(sourceCode, l->tokens_num);;
    if (l->tokens[0].type == LabelDefinition) {
        l->has_label = TRUE;
        l->label = l->tokens[0];
        ++l->tokens;
        l->tokens_num--;
    }
    l->address = address;
    l->binary_command = tokensToBinary(l->tokens);
    return l;
}

