#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "Token.h"


#define TRUE 1
#define FALSE 0


int isString(char* word){ /*TODO check .asciz definition*/
    int i;
    if (word[0] != '"'){
        return FALSE;
    }
    if (word[strlen(word)-1] != '"'){
        return FALSE;
    }

    for (i = 1; i < strlen(word) - 1; ++i) {
        if (word[i] == '"'){
            return FALSE;
        }
    }
    return TRUE;
}

int isCommandWord(char* word){
    char* commandWords[] = {"add", "sub", "and", "or", "nor", "move", "mhvi", "mvlo",
                            "addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt",
                            "bgt", "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call",
                            "stop"};
    /*TODO no magic numbers*/
    int i;
    for (i = 0; i < 27; ++i) {
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
