#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Token.h"
#include "../utils/string_utils.h"


#define TRUE 1
#define FALSE 0


int isString(char* word){
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
                            "stop", ".db", ".dh", ".dw", ".entry", ".extern", ".asciz"};
    /*TODO no magic numbers*/
    int i;
    for (i = 0; i < 33; ++i) {
        if (strcmp(word, commandWords[i]) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

int isNumber(const char* word){
    int i = 0;
    if (word[0] == '-' || word[0] == '+'){
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



Token wordToToken(char* word, int position){
    Token t;
    t.content = stringDuplicate(word);
    if (strlen(word) == 0){
        t.type = Empty;
    } else if(word[0] == '$'){
        t.type = Register;
    } else if(isCommandWord(word)){
        t.type = Command;
    } else if (isNumber(word)){
        t.type = Number;
    } else if (isString(word)){
        t.type = String;
    } else if (word[strlen(word)-1] == ':'){
        t.type = LabelDefinition;
    } else if (position == 0){ /* first token without ':' has to be command name*/
        t.type = Command;
    } else {
        t.type = Label;
    }
    return t;
}

void destroyToken(Token t){
    free(t.content);
}
