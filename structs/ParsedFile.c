#include "LineOfCode.h"
#include "Token.h"
#include "BinaryCommand.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ParsedFile.h"

int countLines(char *text) {
    return 0; /* TODO */
}

char **splitLines(char *text) {
    return NULL; /* TODO */
}

LineOfCode *parseLines(char **source_lines, int lines_num) {
    return NULL; /* TODO */
}

ParsedFile *createParsedFile(char *filename) {
    char* text = ""; /* read(filename, ...); */
    int lines_num = countLines(text);
    char** source_lines = splitLines(text);
    ParsedFile *parsed_file = malloc(sizeof(parsed_file));
    parsed_file->lines_num = lines_num;
    parsed_file->lines = parseLines(source_lines, lines_num);
    return parsed_file;
}