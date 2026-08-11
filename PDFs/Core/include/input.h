#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>


void readString(const char *prompt, char *buffer, size_t size);
int readInt(const char *prompt);
void trimWhitespace(char *str);
int validateInputString(const char *str);

#endif 