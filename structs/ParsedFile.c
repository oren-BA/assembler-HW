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
    return split(text, 1, delim, 1);
}

LineOfCode **parseLines(char **source_lines, int lines_num) {
    LineOfCode **lines = malloc(sizeof(void *) * lines_num);
    for (int i = 0; i < lines_num; ++i) {
        lines[i] = createLine(source_lines[i]);
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
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer) {
        // start to process your data / extract strings here...
        source_lines = splitLines(buffer, lines_num);
    } else {
        /*TODO handle error*/
    }

    ParsedFile *parsed_file = malloc(sizeof(*parsed_file));
    parsed_file->lines_num = lines_num;
    parsed_file->lines = parseLines(source_lines, lines_num);
    return parsed_file;
}

void printAddress(int address){
    char str[5];
    int len;
    snprintf(str, 5, "%d", address);
    len = strlen(str);
    char adr[5] = {'0','0','0','0','\0'};
    for (int i = 0; i < len; ++i) {
        adr[i+(4-len)] = str[i];
    }
    printf("%s ", adr);
}

void printPayload(char* payload, int size){
    int i;
    for (i = 0; i < size; ++i) {
        printf("%c", payload[i]);
        if (i%2 == 1) printf(" ");
    }
}

void printFile(ParsedFile file){
    int i;
    LineOfCode line;
    for (i = 0; i < file.lines_num; ++i) {
        line = *file.lines[i];
        printAddress(line.address);
        printPayload(line.binary->payload, line.binary->size);
    }
}