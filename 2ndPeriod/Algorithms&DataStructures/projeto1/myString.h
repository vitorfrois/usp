#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <stdbool.h>

char* readString(int separator);

char *readword(FILE *stream, char sep);

char *readline(FILE *stream);

#endif