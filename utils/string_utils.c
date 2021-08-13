#define FALSE 0
#define TRUE 1


char** split(char* text, int word_num, char* delimiters, int delimiters_num){
    int is_delimiter;
    int i;
    int end = 0;
    int start = 0;
    char** words = (char**)malloc(sizeof(char*) * word_num);
    int word_index = 0;
    int wordLen;
    while (text[end] != '\n'){
        /*TODO add support for consecutive whitespaces*/
        is_delimiter = FALSE;
        for (i = 0; i < delimiters_num; ++i) {
            if (text[end] == delimiters[i]){
                is_delimiter = TRUE;
                break;
            }
        }
        if (is_delimiter){
            wordLen = end-start;
            /* +1 for null terminator */
            words[word_index] = malloc(sizeof(char) * (wordLen + 1));
            memcpy(words[word_index], text + start, wordLen );
            words[word_index][wordLen] = '\0';
            start = end+1;
            end++;
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