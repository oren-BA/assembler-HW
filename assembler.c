#include <stdlib.h>
#include "structs/ParsedFile.h"
#include "structs/LineOfCode.h"
#include "SymbolTable.h"


#define FALSE 0 /* TODO*/

#define TRUE 1

#define BYTE_SIZE 8

#define CODE_SIZE 4

char *dataTokenToPayload(char *data_instruction, char *data_argument) {
    if (strcmp(data_instruction, ".dw") == 0){
    }
}

void write_bit_characters(char* str_payload, int value, int size){
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

BinaryCommand* dataLineToBinary(LineOfCode line) {
    unsigned int size = 0;
    char* mask = NULL;
    char* payload = NULL;
    char *data_instruction;
    int number;
    int word_size = 0;
    int i;
    int j;
    int opcode;
    int funct;
    int rd, rs, rt;
    enum LineType line_type = getLineType(line);
    int values[6];
    int sizes[6];
    BinaryCommand* binary;

    if (line_type == ASCII){
        size = strlen(line.tokens[1].content) - 2; /* -2 to get the size without the quotes */
        payload = malloc(size);
        memcpy(payload, line.tokens[1].content + 1, size);
        mask = malloc(size);
        for (i = 0; i < size; ++i) {
            mask[i] = (char)0xff;
        }
    }
    else if (line_type == D){
        data_instruction = line.tokens[0].content;
        if(strcmp(data_instruction, ".dw") == 0) word_size = 4;
        else if(strcmp(data_instruction, ".dh") == 0) word_size = 2;
        else if(strcmp(data_instruction, ".db") == 0) word_size = 1;
        size = (line.tokens_num - 1) * word_size;
        payload = malloc(size);
        for (i = 1; i < line.tokens_num; ++i) {
            number = strtol(line.tokens[i].content, NULL, 10);
            for (j = 0; j < word_size; ++j) {
                payload[i*word_size + j] = (char)(number>>BYTE_SIZE*j & 0xff);
            }
        }
        mask = malloc(size);
        for (i = 0; i < size; ++i) {
            mask[i] = (char)0xff;
        }
    }
    else{
        payload = malloc(CODE_SIZE);
        char str_payload[33];
        int start = 31;
        str_payload[32] = '\0';
        if (getLineType(line) == R){
            /* unused*/
            values[0] = 0;
            sizes[0] = 6;
            sizes[1] = 5;
            if (strcmp(line.tokens[0].content, "add") == 0){
                values[1] = 1;
                values[5] = 0;
            }
            else if (strcmp(line.tokens[0].content, "sub") == 0){
                values[1] = 2;
                values[5] = 0;
            }
            else if (strcmp(line.tokens[0].content, "and") == 0){
                values[1] = 3;
                values[5] = 0;
            }
            else if (strcmp(line.tokens[0].content, "or") == 0){
                values[1] = 4;
                values[5] = 0;
            }
            else if (strcmp(line.tokens[0].content, "nor") == 0){
                values[1] = 5;
                values[5] = 0;
            }
            else if (strcmp(line.tokens[0].content, "move") == 0){
                values[1] = 1;
                values[5] = 1;
            }
            else if (strcmp(line.tokens[0].content, "mvhi") == 0){
                values[1] = 2;
                values[5] = 1;
            }
            else if (strcmp(line.tokens[0].content, "mvlo") == 0){
                values[1] = 3;
                values[5] = 1;
            }
            sizes[2] = 5;
            sizes[3] = 5;
            sizes[4] = 5;
            sizes[5] = 6;
            values[2] = strtol(line.tokens[1].content+1, NULL, 10);
            values[3] = strtol(line.tokens[2].content+1, NULL, 10);
            values[4] = strtol(line.tokens[3].content+1, NULL, 10);
        }
        for (i = 0; i < 6; ++i) {
            write_bit_characters((char*)(&str_payload) + start, values[i], sizes[i]);
            start -= sizes[i];
        }
        *(int*)payload = strtol(str_payload, NULL, 2);
    }

    binary = createBinary(size, payload, mask);
    return binary;
}



int first_pass(ParsedFile *file) {
    unsigned int IC = 100;
    unsigned int DC = 0;
    int label_exists = FALSE;
    SymbolTable* symbol_table = createSymbolTable();
    int line_index;
    for (line_index = 0; line_index < file->lines_num; ++line_index) {
        LineOfCode line = *file->lines[line_index];
        if (getLineType(line) == ASCII || getLineType(line) == D) {
            if (line.has_label){
                insertSymbol(symbol_table, line.label.content, DC, DATA);
                label_exists = TRUE;
            }
            line.binary = dataLineToBinary(line);
            DC += line.binary->size;
            continue;
        }
        else if (getLineType(line) == ENTRY){
            continue;
        }
        else if (getLineType(line) == EXTERN){
            insertSymbol(symbol_table, line.tokens[1].content, 0, EXTERN);
            continue;
        }
        else { /* code line */
            if (line.has_label){
                insertSymbol(symbol_table, line.label.content, IC, CODE);
            }
            line.binary = dataLineToBinary(line);
        }


    }
   return 0;
}

