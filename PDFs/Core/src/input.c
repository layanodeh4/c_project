#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

void trimWhitespace(char *str) {
    if (str == NULL) return;

    // Trim leading space
    char *start = str;
    while (isspace((unsigned char)*start)) start++;

    if (*start == 0) {
        *str = 0;
        return;
    }

    // Trim trailing space
    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    end[1] = '\0';

    // Move trimmed string to original buffer
    memmove(str, start, end - start + 2);
}

void readString(const char *prompt, char *buffer, size_t size) {
    if (prompt) printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
        trimWhitespace(buffer);
    }
}

int readInt(const char *prompt) {
    char buffer[64];
    int value;

    while (1) {
        readString(prompt, buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &value) == 1) {
            return value;
        }
        printf("Invalid input. Please enter a valid number.\n");
    }
}