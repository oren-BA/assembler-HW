#ifndef ASSEMBLER_HW_PARSEDFILE_H
#define ASSEMBLER_HW_PARSEDFILE_H


#include "LineOfCode.h"

typedef struct parsedFile ParsedFile;
struct parsedFile{
    LineOfCode **lines;
    int lines_num;
};
ParsedFile* createParsedFile(char* filename);
void printExtern(ParsedFile file, FILE *fp);
char **splitLines(char *text, int i);
LineOfCode **parseLines(char **source_lines, int lines_num);
int countLines(char* filename);
void printFile(ParsedFile file, FILE *fp);
void printAddress(unsigned int address, FILE *fp);

#endif
