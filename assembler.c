#include <stdlib.h>
#include "structs/ParsedFile.h"
#include "structs/SymbolTable.h"


#define FALSE 0

#define TRUE 1

#define BYTE_SIZE 8

#define CODE_SIZE 4



void write_bit_characters(char *str_payload, unsigned int value, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        unsigned int bit = value % 2;
        if (bit == 0)
            str_payload[-i] = '0';
        else
            str_payload[-i] = '1';
        value = value >> 1;
    }
}

int isConditionalBranch(char* content){
    char *branch_commands[] = {"bne", "beq", "blt","bgt"};
    int i;
    for (i = 0; i < 4; ++i) {
        if (strcmp(content, branch_commands[i]) == 0) return TRUE;
    }
    return FALSE;
}

int getImmediateLocation(char *content) {
    if (isConditionalBranch(content))
        return 4;
    return 3;
}

BinaryCommand *dataLineToBinary(LineOfCode* line) {
    unsigned int size = 0;
    char str_payload[33];
    int start;
    char *payload = NULL;
    char *data_instruction;
    unsigned int number;
    int word_size = 0;
    int word_num =0;
    int i;
    int j;
    int immediate_location;
    int rs_loc;
    int rt_loc;
    unsigned int rd, rs, rt = 0;
    enum LineType line_type = getLineType(line);
    unsigned int values[6];
    int sizes[6];
    BinaryCommand *binary;
    char *i_commands[] = {"addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt",
                          "bgt", "lb", "sb", "lw", "sw", "lh", "sh"};

    if (line_type == ASCII) {
        /* -2 to get the size without the quotes, +1 for null terminator*/
        size = strlen(line->tokens[1].content) - 2 + 1;
        payload = malloc(size);
        memcpy(payload, line->tokens[1].content + 1, size);
        payload[size-1] = '\0';
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
                payload[(i-1) * word_size + j] = (char) ((number >> (BYTE_SIZE * j)) & 0xff);
            }
        }
    } else {
        payload = malloc(CODE_SIZE);
        start = 31;
        size = 4;
        str_payload[32] = '\0';
        if (getLineType(line) == R) {
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
            if (line->tokens_num >= 4){
                rs = strtoul(line->tokens[1].content + 1, NULL, 10);
                rt = strtoul(line->tokens[2].content + 1, NULL, 10);
                rd = strtoul(line->tokens[3].content + 1, NULL, 10);
            } else {
                rd = strtoul(line->tokens[1].content + 1, NULL, 10);
                rs = strtoul(line->tokens[2].content + 1, NULL, 10);
            }
            values[2] = rd;
            values[3] = rt;
            values[4] = rs;

        } else if (getLineType(line) == I) {
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
            rt_loc = (3*4)/immediate_location;
            values[0] = strtoul(line->tokens[immediate_location-1].content, NULL, 10);
            values[1] = strtoul(line->tokens[rt_loc-1].content + 1, NULL, 10);
            values[2] = strtoul(line->tokens[rs_loc].content + 1, NULL, 10);
        } else {
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
                values[0] = strtoul(line->tokens[1].content + 1, NULL, 10);
            }
        }
        for (i = 0; i < word_num; ++i) {
            write_bit_characters((char *) (&str_payload) + start, values[i], sizes[i]);
            start -= sizes[i];
        }
        *(unsigned int *) payload = strtoul(str_payload, NULL, 2);
    }

    binary = createBinary(size, payload);
    free(payload);
    return binary;
}

void updateDataSymbolsAddress(SymbolTable *table, unsigned int ICF) {
    struct SymbolTableEntry *entry = table->first;
    while (entry != NULL){
        if ((entry->attributes & DATA) != 0){
            entry->value += ICF;
        }
        entry = entry->next;
    }
}

void updateDataLinesAddress(ParsedFile *file, unsigned int ICF) {
    LineOfCode *line;
    int i;
    for (i = 0; i < file->lines_num; ++i) {
        line = file->lines[i];
        if (getLineType(line) == D || getLineType(line) == ASCII){
            line->address += ICF;
        }
    }
}

int first_pass(ParsedFile *file, SymbolTable *symbol_table, unsigned int* ICF, unsigned int* DCF) {
    int line_index;
    unsigned int IC = 100;
    unsigned int DC = 0;
    int had_error = FALSE;
    for (line_index = 0; line_index < file->lines_num; ++line_index) {
        LineOfCode* line = file->lines[line_index];
        if (line->is_empty_or_comment)
            continue;
        if (!validate_line(*line)){
            had_error = TRUE;
            continue;
        }
        if (getLineType(line) == ASCII || getLineType(line) == D) {
            if (line->has_label) {
                if (insertSymbol(symbol_table, line->label.content, DC, DATA) == LABEL_ALREADY_EXISTS_ERROR){
                    printf("Line %d: symbol \"%s\" already exists\n", line->line_no, line->label.content);
                    had_error = TRUE;
                }
            }
            line->binary = dataLineToBinary(line);
            line->address = DC;
            DC += line->binary->size;
            continue;
        } else if (getLineType(line) == E && strcmp(line->tokens[0].content, ".entry") == 0) {
            continue;
        } else if (getLineType(line) == E) {
            if (insertSymbol(symbol_table, line->tokens[1].content, 0, EXTERN) == LABEL_ALREADY_EXISTS_ERROR) {
                printf("Line %d: symbol \"%s\" already exists\n", line->line_no, line->tokens[1].content);
                had_error = TRUE;
            }

            continue;
        } else { /* code line */
            if (line->has_label) {
                if (insertSymbol(symbol_table, line->label.content, IC, CODE) == LABEL_ALREADY_EXISTS_ERROR){
                    printf("Line %d: symbol \"%s\" already exists\n", line->line_no, line->label.content);
                    had_error = TRUE;
                }
            }
            line->binary = dataLineToBinary(line);
            line->address = IC;
            IC += 4;
        }
    }
    *ICF = IC;
    *DCF = DC;
    updateDataSymbolsAddress(symbol_table, *ICF);
    updateDataLinesAddress(file, *ICF);
    return !had_error;
}

int completeBinary(SymbolTable *table, LineOfCode *line) {
    SymbolTableEntry *entry;
    char *symbol;
    unsigned int mask, offset;
    unsigned int value;
    if (getLineType(line) == J && strcmp(line->tokens[0].content, "stop") != 0){
        symbol = line->tokens[1].content;
        if (symbol[0] == '$')
            return EXIT_SUCCESS; /* no need to fix register binary*/
        value = getEntry(table, symbol)->value;
        mask = 0x1ffffff;
        *(unsigned int*)line->binary->payload = (*(unsigned int*)line->binary->payload & (~mask)) | (value & mask);
    }
    if (getLineType(line) == I){
        if (isConditionalBranch(line->tokens[0].content)){
            entry = getEntry(table, line->tokens[3].content);
            if (entry == NULL){
                printf("line %d: no such symbol \"%s\"\n", line->line_no, line->tokens[3].content);
                return EXIT_FAILURE;
            }
            if ((entry->attributes & EXTERN) != 0){
                printf("line %d: can't use external symbol with conditional branch\n", line->line_no);
                return EXIT_FAILURE;
            }
            offset = entry->value - line->address;
            mask = 0xffff;
            *(unsigned int*)line->binary->payload = (*(unsigned int*)line->binary->payload & (~mask)) | (offset & mask);
        }
    }
    return EXIT_SUCCESS;
}

int second_pass(ParsedFile *file, SymbolTable *symbol_table){
    int line_index;
    int had_error = FALSE;
    for (line_index = 0; line_index < file->lines_num; ++line_index) {
        LineOfCode* line = file->lines[line_index];
        if (!line->is_empty_or_comment && line->tokens[0].content[0] == '.'){
            if (strcmp(line->tokens[0].content, ".entry") == 0){
                if (addAttribute(symbol_table, line->tokens[1].content, ENTRY) == NO_SUCH_SYMBOL_ERROR){
                    printf("no such symbol: \"%s\"\n", line->tokens[1].content);
                    had_error = TRUE;
                }
            }
            continue;
        }
        /* code line */
        if (completeBinary(symbol_table, line) == EXIT_FAILURE){
            had_error = TRUE;
        }
        if (getLineType(line) == J
            && strcmp(line->tokens[0].content, "stop") != 0
            && line->tokens[1].content[0] != '$'
            && ((getEntry(symbol_table, line->tokens[1].content)->attributes & EXTERN) != 0)){
            /* J instruction (except stop) that uses a label attributed as external */
            line->using_extern = TRUE;
        }
    }
    return !had_error;
}


