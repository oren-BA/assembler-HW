#include <memory.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

int in_string(char c, const char *str, int length) {
    int i;
    for (i = 0; i < length; ++i) {
        if (c == str[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

char* stringDuplicate(char* str){
    char* new_str;
    strcpy(new_str = malloc(strlen(str) + 1), str);
    return new_str;
}

char **split(char *text, int word_num, const char *delimiters, int delimiters_num) {
    int end = 0;
    int start = 0;
    char **words = (char **) malloc(sizeof(char *) * word_num);
    int word_index = 0;
    int wordLen;
    while (text[end] != '\0') {
        if (in_string(text[end], delimiters, delimiters_num)) {
            wordLen = end - start;
            /* +1 for null terminator */
            words[word_index] = malloc(sizeof(char) * (wordLen + 1));
            memcpy(words[word_index], text + start, wordLen);
            words[word_index][wordLen] = '\0';
            start = end + 1;
            word_index++;
        }
        end++;
    }
    /* Handle last word */
    wordLen = end - start;
    words[word_index] = malloc(sizeof(char) * (wordLen + 1)); /* +1 for null terminator */
    memcpy(words[word_index], text + start, wordLen);
    words[word_index][wordLen] = '\0';
    return words;
}



int countUselessWhiteSpace(char* word){
    int count = 0;
    int in_string = FALSE;
    int i = 0;
    int has_label = FALSE;
    while(word[i] == ' ' || word[i] == '\t'){ /*removes leading whitespaces*/
        count++;
        i++;
    }
    while (word[i] != ' ' && word[i] != '\t' && word[i] != '\0'){
        i++;
    }
    if (word[i] == ' ' || word[i] == '\t'){
        if (word[i-1] == ':')
            has_label = TRUE;
        i++;
    }
    if (has_label){ /*handle second non-useless whitespace*/
        while(word[i] == ' ' || word[i] == '\t'){ /*removes leading whitespaces*/
            count++;
            i++;
        }
        while (word[i] != ' ' && word[i] != '\t' && word[i] != '\0'){
            i++;
        }
        if (word[i] == ' ' || word[i] == '\t'){
            i++;
        }
    }
    while (word[i] != '\0'){
        if (word[i] == '\"') {
            if (in_string) {
                in_string = FALSE;
            } else {
                in_string = TRUE;
            }
        }
        if (!in_string && word[i] == ' '){
            count++;
        }
        i++;
    }
    return count;
}

char* eliminateWhiteSpace(char* word){
    int new_word_size = strlen(word) - countUselessWhiteSpace(word) ;
    char* new_word = malloc(new_word_size + 1);
    int i = 0;
    int i_new = 0;
    int in_string = FALSE;
    int has_label = FALSE;
    new_word[new_word_size] = '\0';
    while(word[i] == ' '){
        i++;
    }
    while (word[i] != ' ' && word[i] != '\0'){
        new_word[i_new] = word[i];
        i++;
        i_new++;
    }
    if (word[i] == ' '){
        new_word[i_new] = word[i];
        if (word[i-1] == ':') has_label = TRUE;
        i++;
        i_new++;
    }
    if (has_label){ /*handle second non-useless whitespace*/
        while(word[i] == ' '){
            i++;
        }
        while (word[i] != ' ' && word[i] != '\0'){
            new_word[i_new] = word[i];
            i++;
            i_new++;
        }
        if (word[i] == ' '){
            new_word[i_new] = word[i];
            if (word[i--] == ':') has_label = TRUE;
            i++;
            i_new++;
        }
    }
    while (word[i] != '\0'){
        if (word[i] == '\"') {
            if (in_string) {
                in_string = FALSE;
            } else {
                in_string = TRUE;
            }
        }
        if (!in_string && word[i] == ' '){
            i++;
        } else {
            new_word[i_new] = word[i];
            i++;
            i_new++;
        }
    }
    return new_word;
}

char **split2(char *old_text, int word_num) {
    char* text = eliminateWhiteSpace(old_text);
    int end = 0;
    int start = 0;
    char **words = (char **) malloc(sizeof(char *) * word_num);
    int word_index = 0;
    int is_string = FALSE;
    int wordLen;
    while (text[end] != '\0') { // a  b
        if (text[end] == '\"') {
            if (is_string) {
                is_string = FALSE;
            } else {
                is_string = TRUE;
            }
        }
        if (!is_string) {
            if ((text[end] == ',' || text[end] == ' ')) {
                wordLen = end - start;
                /* +1 for null terminator */
                words[word_index] = malloc(sizeof(char) * (wordLen + 1));
                memcpy(words[word_index], text + start, wordLen);
                words[word_index][wordLen] = '\0';
                start = end + 1;
                word_index++;
            }
        }
        end++;
    }
    /* Handle last word */
    wordLen = end - start;
    /* +1 for null terminator */
    words[word_index] = malloc(sizeof(char) * (wordLen + 1));
    memcpy(words[word_index], text + start, wordLen);
    words[word_index][wordLen] = '\0';
    start = end + 1;
    word_index++;

    return words;
}







