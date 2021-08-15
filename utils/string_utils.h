#ifndef ASSEMBLER_HW_STRING_UTILS_H
#define ASSEMBLER_HW_STRING_UTILS_H

char** split(char* text, int word_num, char* delimiters, int delimiters_num);
char **split2(char *text, int word_num);
int countUselessWhiteSpace(char* word);
char* eliminateWhiteSpace(char* word);

#endif /* ASSEMBLER_HW_STRING_UTILS_H */
