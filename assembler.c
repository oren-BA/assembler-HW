#include <stdlib.h>
#include "structs/ParsedFile.h"
#include "structs/LineOfCode.h"
#include "SymbolTable.h"


#define FALSE 0 /* TODO*/

#define TRUE 1

#define BYTE_SIZE 8

#define CODE_SIZE 4


char *dataTokenToPayload(char *data_instruction, char *data_argument) {
    if (strcmp(data_instruction, ".dw") == 0) {
    }
}

void write_bit_characters(char *str_payload, int value, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        int bit = value % 2;
        if (bit == 0)
            str_payload[-i] = '0';
        else
            str_payload[-i] = '1';
        value = value >> 1;
    }
}

int getImmediateLocation(char *content) {
    char *branch_commands[] = {"bne", "beq", "blt","bgt"};
    int i;
    for (i = 0; i < 4; ++i) {
        if (strcmp(content, branch_commands[i]) == 0) return 4;
    }
    return 3;
}

BinaryCommand *dataLineToBinary(LineOfCode* line) {
    unsigned int size = 0;
    char *mask = NULL;
    char *payload = NULL;
    char *data_instruction;
    int number;
    int word_size = 0;
    int word_num =0;
    int i;
    int j;
    int opcode;
    int funct;
    int immediate_location;
    int rs_loc;
    int rt_loc;
    int rd, rs, rt;
    enum LineType line_type = getLineType(line);
    int values[6];
    int sizes[6];
    BinaryCommand *binary;
    char *i_commands[] = {"addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt",
                          "bgt", "lb", "sb", "lw", "sw", "lh", "sh"};
    char *j_commands[] = {"addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt",
                          "bgt", "lb", "sb", "lw", "sw", "lh", "sh"};

    if (line_type == ASCII) {
        size = strlen(line->tokens[1].content) - 2; /* -2 to get the size without the quotes */
        payload = malloc(size);
        memcpy(payload, line->tokens[1].content + 1, size);
        mask = malloc(size);
        for (i = 0; i < size; ++i) {
            mask[i] = (char) 0xff;
        }
    } else if (line_type == D) {
        data_instruction = line->tokens[0].content;
        if (strcmp(data_instruction, ".dw") == 0) word_size = 4;
        else if (strcmp(data_instruction, ".dh") == 0) word_size = 2;
        else if (strcmp(data_instruction, ".db") == 0) word_size = 1;
        size = (line->tokens_num - 1) * word_size;
        payload = malloc(size);
        for (i = 1; i < line->tokens_num; ++i) {
            number = strtol(line->tokens[i].content, NULL, 10);
            for (j = 0; j < word_size; ++j) {
                payload[i * word_size + j] = (char) (number >> BYTE_SIZE * j & 0xff);
            }
        }
        mask = malloc(size);
        for (i = 0; i < size; ++i) {
            mask[i] = (char) 0xff;
        }
    } else {
        payload = malloc(CODE_SIZE);
        char str_payload[33];
        int start = 31;
        size = 4;
        str_payload[32] = '\0';
        if (getLineType(line) == R) {
            /* unused*/
            mask = malloc(size);
            for (i = 0; i < size; ++i) {
                mask[i] = (char) 0xff;
            }
            word_num = 6;
            values[0] = 0;
            sizes[0] = 6;
            sizes[1] = 5;
            if (strcmp(line->tokens[0].content, "add") == 0) {
                values[1] = 1;
                values[5] = 0;
            } else if (strcmp(line->tokens[0].content, "sub") == 0) {
                values[1] = 2;
                values[5] = 0;
            } else if (strcmp(line->tokens[0].content, "and") == 0) {
                values[1] = 3;
                values[5] = 0;
            } else if (strcmp(line->tokens[0].content, "or") == 0) {
                values[1] = 4;
                values[5] = 0;
            } else if (strcmp(line->tokens[0].content, "nor") == 0) {
                values[1] = 5;
                values[5] = 0;
            } else if (strcmp(line->tokens[0].content, "move") == 0) {
                values[1] = 1;
                values[5] = 1;
            } else if (strcmp(line->tokens[0].content, "mvhi") == 0) {
                values[1] = 2;
                values[5] = 1;
            } else if (strcmp(line->tokens[0].content, "mvlo") == 0) {
                values[1] = 3;
                values[5] = 1;
            }
            sizes[2] = 5;
            sizes[3] = 5;
            sizes[4] = 5;
            sizes[5] = 6;
            values[2] = strtol(line->tokens[3].content + 1, NULL, 10);
            values[3] = strtol(line->tokens[2].content + 1, NULL, 10);
            values[4] = strtol(line->tokens[1].content + 1, NULL, 10);
        } else if (getLineType(line) == I) {
            /*TODO handle mask*/
            word_num = 4;

            for (i = 0; i < 15; ++i) {
                if (strcmp(line->tokens[0].content, i_commands[i]) == 0){
                    values[3] = i+10;
                }
            }
            sizes[0] = 16;
            sizes[1] = 5;
            sizes[2] = 5;
            sizes[3] = 6;
            rs_loc = 1;
            immediate_location = getImmediateLocation(line->tokens[0].content);
            mask = malloc(size);
            for (i = 0; i < size; ++i) {
                mask[i] = (char) 0xff;
            }
            if (immediate_location == 4){
                mask[0] = 0;
                mask[1] = 0;
            }
            rt_loc = (3*4)/immediate_location;
            values[0] = strtol(line->tokens[immediate_location-1].content, NULL, 10);
            values[1] = strtol(line->tokens[rt_loc-1].content + 1, NULL, 10);
            values[2] = strtol(line->tokens[rs_loc].content + 1, NULL, 10);
        } else {
            /*TODO handle mask*/
            mask = malloc(size);
            for (i = 0; i < size; ++i) {
                mask[i] = (char) 0xff;
            }
            word_num = 3;
            sizes[0] = 25;
            sizes[1] = 1;
            sizes[2] = 6;
            if (strcmp(line->tokens[0].content, "jmp") == 0){
                values[2] = 30;
            }
            if (strcmp(line->tokens[0].content, "la") == 0){
                values[2] = 31;
            }
            if (strcmp(line->tokens[0].content, "call") == 0){
                values[2] = 32;
            }
            if (strcmp(line->tokens[0].content, "stop") == 0){
                values[2] = 63;
            }
            values[0] = 0;
            values[1] = 0;
            if (line->tokens[1].type == Register){
                values[1] = 1;
                values[0] = strtol(line->tokens[1].content + 1, NULL, 10);
            } else { /*handle mask*/
                mask[3] = (char) 0xfe;
                for (i = 0; i < 3; ++i) {
                    mask[i] = (char) 0x00;
                }
            }
        }
        for (i = 0; i < word_num; ++i) {
            write_bit_characters((char *) (&str_payload) + start, values[i], sizes[i]);
            start -= sizes[i];
        }
        *(int *) payload = strtol(str_payload, NULL, 2);
    }

    binary = createBinary(size, payload, mask);
    return binary;
}


int first_pass(ParsedFile *file, SymbolTable *symbol_table, unsigned int* ICF, unsigned int* DCF) {
    unsigned int IC = 100;
    unsigned int DC = 0;
    int label_exists = FALSE;
    int line_index;
    for (line_index = 0; line_index < file->lines_num; ++line_index) {
        LineOfCode* line = file->lines[line_index];
        if (line->is_empty_or_comment)
            continue;
        validate_line(*line);
        if (getLineType(line) == ASCII || getLineType(line) == D) {
            if (line->has_label) {
                insertSymbol(symbol_table, line->label.content, DC, DATA);
                label_exists = TRUE;
            }
            line->binary = dataLineToBinary(line);
            DC += line->binary->size;
            continue;
        } else if (getLineType(line) == E && strcmp(line->tokens[0].content, ".entry") == 0) {
            continue;
        } else if (getLineType(line) == E) {
            insertSymbol(symbol_table, line->tokens[1].content, 0, EXTERN);
            continue;
        } else { /* code line */
            if (line->has_label) {
                insertSymbol(symbol_table, line->label.content, IC, CODE);
            }
            line->binary = dataLineToBinary(line);
            IC += 4;
        }
    }
    *ICF = IC;
    *DCF = DC;
    return 0;
}

void completeBinary(SymbolTable *pTable, LineOfCode *pCode) {
    //move to Line.c
}

int getLabelAtrributes(SymbolTable *pTable, char *content) {
    return 0;
}

int second_pass(ParsedFile *file, SymbolTable *symbol_table){
    int line_index;
    for (line_index = 0; line_index < file->lines_num; ++line_index) {
        LineOfCode* line = file->lines[line_index];
        if (line->tokens[0].content[0] == '.'){
            if (strcmp(line->tokens[0].content, ".entry") == 0){
                addAttribute(symbol_table, line->tokens[1], EXTERN);
            }
            continue;
        }
        /* code line */
        completeBinary(symbol_table, line);
        if (getLineType(line) == J
            && strcmp(line->tokens[0].content, "stop") != 0
            && ((getLabelAtrributes(symbol_table, line->tokens[1].content) & EXTERN) != 0)){
            /* J instruction (except stop) that uses a label attributed as external */
            line->using_extern = TRUE;
        }
    }
    return 0;
}


