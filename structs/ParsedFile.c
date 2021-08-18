#include "LineOfCode.h"
#include "Token.h"
#include "BinaryCommand.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ParsedFile.h"
#include "../utils/string_utils.h"

int countLines(char *filename) {
    FILE *fp = fopen(filename, "r");
    int ch = 0;
    int lines = 0;
    if (fp == NULL) {
        return 0;
    }
    lines++;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            lines++;
        }
    }
    fclose(fp);
    return lines;
}

char **splitLines(char *text, int lines_num) {
    char delim[1] = {'\n'};
    return split(text, lines_num, delim, 1);
}

LineOfCode **parseLines(char **source_lines, int lines_num) {
    LineOfCode **lines = malloc(sizeof(void *) * lines_num);
    char* curr_line;
    int i;
    for (i = 0; i < lines_num; ++i) {
        curr_line = source_lines[i];
        lines[i] = createLine(curr_line,i);
    }
    return lines;
}

ParsedFile *createParsedFile(char *filename) {
    long length;
    char *buffer = NULL;
    char **source_lines = NULL;
    int lines_num = countLines(filename);
    FILE *f = fopen(filename, "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f) - 21;
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length+1);
        if (buffer) {
            fread(buffer, 1, length, f);
            buffer[length] = '\0';
        }
        fclose(f);
    }

    if (buffer) {
        source_lines = splitLines(buffer, lines_num);
    } else {
        /*TODO handle error*/
    }

    ParsedFile *parsed_file = malloc(sizeof(*parsed_file));
    parsed_file->lines_num = lines_num;
    parsed_file->lines = parseLines(source_lines, lines_num);
    return parsed_file;
}

void printAddress(unsigned int address){
    char str[5];
    int len;
    int i;
    snprintf(str, 5, "%d", address);
    len = strlen(str);
    char adr[5] = {'0','0','0','0','\0'};
    for ( i = 0; i < len; ++i) {
        adr[i+(4-len)] = str[i];
    }
    printf("%s", adr);
}

void printPayload(char* payload, unsigned int size,unsigned int byte_count,unsigned int address){
    int i;
    char* c;
    for (i = 0; i < size; ++i) {
        if (byte_count % 4 == 0){
            if (byte_count > 0){
                printf("\n");
            }
            printAddress(address + byte_count);
        }
        byte_count++;
        c = payload+i;
        printf(" %x", c[0] & 0xff);
    }
}

void printFile(ParsedFile file){
    int i;
    LineOfCode* line;
    int start_address = 100;
    unsigned int byte_count = 0;
    for (i = 0; i < file.lines_num; ++i) {
        line = file.lines[i];
        if (line->is_empty_or_comment || getLineType(line) == E)
            continue;
        printPayload(line->binary->payload, line->binary->size, byte_count, start_address);
        byte_count += line->binary->size;
    }
}