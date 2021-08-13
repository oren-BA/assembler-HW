#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "Token.h"


bool isString(char* word){ /*TODO check .asciz definition*/
    if (word[0] != '"'){
        return false;
    }
    if (word[strlen(word)-1] != '"'){
        return false;
    }
    int i;
    for (i = 1; i < strlen(word) - 1; ++i) {
        if (word[i] == '"'){
            return false;
        }
    }
    return true;
}

bool isCommandWord(char* word){
    char* commandWords[] = {"add", "sub", "and", "or", "nor", "move", "mhvi", "mvlo",
                            "addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt",
                            "bgt", "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call",
                            "stop"};
    /*TODO no magic numbers*/
    int i;
    for (i = 0; i < 27; ++i) {
        if (strcmp(word, commandWords[i]) == 0){
            return true;
        }
    }
    return false;
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
