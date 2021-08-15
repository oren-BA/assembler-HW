#include <stdlib.h>
#include <math.h>
#include "../utils/string_utils.h"


#include "Token.h"
#include "LineOfCode.h"

#define TRUE 1
#define FALSE 0
#define R_COMMANDS_NUM 8
#define I_COMMANDS_NUM 15
#define J_COMMANDS_NUM 4
#define D_COMMANDS_NUM 3
#define E_COMMANDS_NUM 2

#define ERROR 2


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
        tokens[i] = wordToToken(words[i],i);
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

int isDigit(char c) {
    if ((c >= '0' && c <= '9')) return TRUE;
    return FALSE;
}

int isLetter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return TRUE;
    return FALSE;
}


int validateLabel(char *w, int isDefinition) {
    unsigned int len = strlen(w);
    int i;
    if (!isLetter(w[0])) return FALSE;
    for (i = 1; i < len - 1; ++i) {
        if (!isLetter(w[i]) && !isDigit(w[i])) return FALSE;
    }
    if (len > 1) {
        if (isDefinition) {
            if (w[len - 1] != ':') return FALSE;
        } else if (!isLetter(w[i]) && !isDigit(w[i])) return FALSE;
    }
    return TRUE;
}

enum LineType getLineType(LineOfCode* line) {
    /*TODO change default return to ERROR*/
    char *cmd = line->tokens[0].content;
    int i;
    char *r_commands[] = {"add", "sub", "and", "or", "nor", "move", "mhvi", "mvlo"};
    char *i_commands[] = {"addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt",
                          "bgt", "lb", "sb", "lw", "sw", "lh", "sh"};
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
    for (i = 0; i < I_COMMANDS_NUM; ++i) {
        if (strcmp(cmd, i_commands[i]) == 0) {
            return I;
        }
    }
    return TypeError;
}


int validateTypeOrder(Token *tokens, int token_num, const enum TokenType *types, int types_num, int line_no) {
    int i;
    int check = TRUE;
    if (token_num != types_num) check = FALSE;
    for (i = 0; i < token_num; i++) {
        if (tokens[i].type != types[i]) check = FALSE;
    }
    if (!check) {
        printf("Line %d: incorrect operands", line_no);
    }
    return check;
}

int validateRegister(char *text) {
    int regNum;
    unsigned int len = strlen(text);
    if (len != 2 && len != 3) return FALSE;
    if (text[0] != '$') return FALSE;
    if (len == 2 && isDigit(text[1]) == FALSE) return FALSE;
    if (len == 3 && (isDigit(text[1]) == FALSE || isDigit(text[2]) == FALSE)) return FALSE;
    regNum = strtol(text + 1, NULL, 10);
    if (regNum > 31) return FALSE;
    return TRUE;
}

int validateToken(Token t, int line_no) {
    int check = TRUE;
    if (strlen(t.content) == 0) {
        check = FALSE;
        printf("Line %d: internal error - empty token\n", line_no);
    }
    if (t.type == Register) {
        check = validateRegister(t.content);
        if (!check) printf("Line %d: invalid register\n", line_no);
    }
    if (t.type == LabelDefinition) {
        check = validateLabel(t.content, TRUE);
        if (!check) printf("Line %d: invalid Label\n", line_no);
    }
    if (t.type == Label) {
        check = validateLabel(t.content, FALSE);
        if (!check) printf("Line %d: invalid Label\n", line_no);
    }
    return check;
}

int validateR(LineOfCode line) {
    enum TokenType types[4] = {Command, Register, Register, Register};
    if (line.tokens_num != 4) {
        printf("Line %d: extraneous operand\n", line.line_no);
        return FALSE;
    } /*checks if line has 4 tokens */
    if (!validateTypeOrder(line.tokens, line.tokens_num, types, 4, line.line_no)) return FALSE;
    return TRUE;
}

int isConditionBranch(const char *cmd) {
    int i;
    char *commands[] = {"beq", "bne", "blt", "bgt"};
    for (i = 0; i < 4; ++i) {
        if (strcmp(cmd, commands[i]) == 0) return TRUE;
    }
    return FALSE;

}


int validateI(LineOfCode line) {
    /*TODO*/
    Token *tokens = line.tokens;
    enum TokenType types[4] = {Command, Register, Register, Label};
    enum TokenType types2[4] = {Command, Register, Number, Register};
    if (line.tokens_num != 4) {
        printf("Line %d: extraneous operand\n", line.line_no);
        return FALSE;
    } /*checks if line has 4 tokens */    /*checks if command is in the condition branch format which is: cmd, reg, reg, label*/
    if (isConditionBranch(tokens[0].content) == TRUE) {
        if (validateTypeOrder(tokens, line.tokens_num, types, 4, line.line_no)) return TRUE;
    } else {     /*checks if command is in the other format which is: cmd, reg, num, reg*/
        if (validateTypeOrder(tokens, line.tokens_num, types2, 4, line.line_no)) {
            return TRUE;
        }
    }
    return FALSE;
}

int validateJ(LineOfCode line) {
    Token *tokens = line.tokens;
    if (strcmp(tokens[0].content, "stop") == 0) {
        if (line.tokens_num == 1) return TRUE;
        printf("Line %d: extraneous operand\n", line.line_no);
        return FALSE;
    }
    if (line.tokens_num != 2) {
        printf("Line %d: extraneous operand\n", line.line_no);
        return FALSE;
    } /*checks if line has 4 tokens */
    if (tokens[1].type == Label) return TRUE;
    if (strcmp(tokens[0].content, "jmp") == 0 && tokens[1].type == Register) {
        return TRUE;
    } else {
        printf("Line %d: incorrect operands", line.line_no);
        return FALSE;
    }

}

int getMaxSize(char *wordType) {
    if (strcmp(wordType, ".db") == 0) {
        return pow(2, 7) - 1;
    } else if (strcmp(wordType, ".dh") == 0) {
        return pow(2, 15) - 1;
    } else {
        return pow(2, 31) - 1;
    }
}

int validateD(LineOfCode line) {
    int i;
    int num;
    int maxNum;
    Token *tokens = line.tokens;
    if (line.tokens_num < 2) {
        printf("Line %d: extraneous operand\n", line.line_no);
        return FALSE;
    }
    maxNum = getMaxSize(tokens[0].content);
    for (i = 1; i < line.tokens_num; ++i) {
        if (tokens[i].type != Number) {
            printf("Line %d: incorrect data type\n", line.line_no);
            return FALSE;
        }
        num = strtol(tokens[i].content, NULL, 10);
        if (num < -(maxNum + 1) || num > maxNum) {
            printf("Line %d: number out of range\n", line.line_no);
            return FALSE;
        }
    }
    return TRUE;
}

int validateE(LineOfCode line) {
    if (line.tokens_num != 2) {
        printf("Line %d: extraneous operand\n", line.line_no);
        return FALSE;
    }
    if (line.tokens[1].type != Label) {
        printf("Line %d: incorrect operand type\n", line.line_no);
        return FALSE;
    }
    return TRUE;
}

int validateAscii(LineOfCode line) {
    if (line.tokens_num != 2) {
        printf("Line %d: extraneous operand\n", line.line_no);
        return FALSE;
    }
    if (line.tokens[1].type != String) {
        printf("Line %d: incorrect operand type\n", line.line_no);
        return FALSE;
    }
    return TRUE;
}

int validate_line(LineOfCode line) {
    int i;
    enum LineType commandType;
    int has_error = FALSE;
    if (line.has_label) {
        if (validateToken(line.label, line.line_no) == FALSE) has_error = TRUE;
    }
    for (i = 0; i < line.tokens_num; ++i) {
        if (validateToken(line.tokens[i], line.line_no) == FALSE) has_error = TRUE;
    }
    commandType = getLineType(&line);
    if (commandType == TypeError) {
        printf("Line %d: unrecognized directive %s\n", line.line_no, line.tokens[0].content);
        has_error = TRUE;
    }
    if (commandType == R) {
        has_error = !validateR(line) || has_error;
    } else if (commandType == I) {
        has_error = !validateI(line) || has_error;
    } else if (commandType == J) {
        has_error = !validateJ(line) || has_error;
    } else if (commandType == D) {
        has_error = !validateD(line) || has_error;
    } else if (commandType == E) {
        has_error = !validateE(line) || has_error;
    } else if (commandType == ASCII) {
        has_error = !validateAscii(line) || has_error;
    } else if (commandType == TypeError) {
        has_error = TRUE;
    } else {
        printf("Line %d: internal error - command type not found\n", line.line_no);
        has_error = TRUE;
    }
    return !has_error; /*returns false if has_error = true*/
}

LineOfCode *createLine(char *sourceCode) {
    /*TODO add line number to line_no*/
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
    l->address = 0;
    l->binary = NULL;
    l->using_extern = FALSE;
    return l;
}

