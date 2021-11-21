/**
 * @brief Function that reads and return string
 * 
 * @param separator if 1, consider ' '; if 0, dont consider ' '
 * @return char* string
 */
char* readString(int separator);

char *readword(FILE *stream, char sep);

char *readline(FILE *stream);