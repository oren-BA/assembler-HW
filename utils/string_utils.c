#include <memory.h>
#include <malloc.h>

#define FALSE 0
#define TRUE 1

int in_string(char c, const char* str, int length){
    int i;
    for (i = 0; i < length; ++i) {
        if (c == str[i]){
            return TRUE;
        }
    }
    return FALSE;
}

char **split(char *text, int word_num, const char *delimiters, int delimiters_num) {
    int end = 0;
    int start = 0;
    char** words = (char**)malloc(sizeof(char*) * word_num);
    int word_index = 0;
    int wordLen;
    while (text[end] != '\0'){
        if (in_string(text[end], delimiters, delimiters_num)){
            wordLen = end-start;
            /* +1 for null terminator */
            words[word_index] = malloc(sizeof(char) * (wordLen + 1));
            memcpy(words[word_index], text + start, wordLen );
            words[word_index][wordLen] = '\0';
            start = end+1;
            word_index++;
        }
        end++;
    }
    /* Handle last word */
    wordLen = end-start;
    words[word_index] = malloc(sizeof(char) * (wordLen + 1)); /* +1 for null terminator */
    memcpy(words[word_index], text + start, wordLen );
    words[word_index][wordLen] = '\0';
    return words;
}
