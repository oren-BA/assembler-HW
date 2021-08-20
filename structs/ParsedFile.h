#ifndef ASSEMBLER_HW_PARSEDFILE_H
#define ASSEMBLER_HW_PARSEDFILE_H


#include <io.h>
#include "LineOfCode.h"

typedef struct parsedFile ParsedFile;
struct parsedFile{
    LineOfCode **lines;
    int lines_num;
};
ParsedFile* createParsedFile(char* filename);
void printExtern(ParsedFile file);
char **splitLines(char *text, int i);
LineOfCode **parseLines(char **source_lines, int lines_num);
int countLines(char* filename);
void printAddress(unsigned int address);
void printFile(ParsedFile file);

#endif
