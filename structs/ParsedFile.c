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
    FILE *fp = fopen(filename, "r");
    char *text = "jmp $4"; /* read(filename, ...); */
    int lines_num = countLines(text);
    char **source_lines = splitLines(text, lines_num);
    ParsedFile *parsed_file = malloc(sizeof(*parsed_file));
    parsed_file->lines_num = lines_num;
    parsed_file->lines = parseLines(source_lines, lines_num);
    return parsed_file;
}