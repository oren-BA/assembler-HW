#include "LineOfCode.h"
#include "Token.h"
#include "BinaryCommand.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ParsedFile.h"
#include "../utils/string_utils.h"

int countLines(char *text) {
    int count = 1;
    int i;

    if (strlen(text) == 0)
        return 0;

    for (i = 0; i < strlen(text); ++i) {
        if (text[i] == '\n')
            ++count;
    }
    return count; /* TODO */
}

char **splitLines(char *text, int lines_num) {
    char delim[1] = {'\n'};
    return split(text, 1, delim, 1);
}

LineOfCode **parseLines(char **source_lines, int lines_num) {
    LineOfCode **lines = malloc(sizeof(void *)*lines_num);
    for (int i = 0; i < lines_num; ++i) {
        lines[i] = createLine(source_lines[i]);
    }
    return lines;
}

ParsedFile *createParsedFile(char *filename) {
    char* text = "MAIN: add $1,$2,$3"; /* read(filename, ...); */
    int lines_num = countLines(text);
    char** source_lines = splitLines(text, lines_num);
    ParsedFile *parsed_file = malloc(sizeof(*parsed_file));
    parsed_file->lines_num = lines_num;
    parsed_file->lines = parseLines(source_lines, lines_num);
    return parsed_file;
}