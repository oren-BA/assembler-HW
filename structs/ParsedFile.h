#ifndef ASSEMBLER_HW_PARSEDFILE_H
#define ASSEMBLER_HW_PARSEDFILE_H

#ifdef __APPLE__
#include <sys/uio.h>
#else
#include <io.h>
#endif
#include "LineOfCode.h"

typedef struct parsedFile ParsedFile;
struct parsedFile{
    LineOfCode **lines;
    int lines_num;
};
ParsedFile* createParsedFile(char* filename);

char **splitLines(char *text, int i);
LineOfCode **parseLines(char **source_lines, int lines_num);
int countLines(char* filename);
void printAddress(unsigned int address);
void printFile(ParsedFile file);

#endif