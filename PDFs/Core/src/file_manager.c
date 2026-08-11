#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_manager.h"
#include "input.h"

int loadDictionaryFromFile(Dictionary *dictionary, const char *filename) {
    if (dictionary == NULL || filename == NULL) return 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }

    char line[1024];
    int validEntries = 0;
    int invalidLines = 0;
    int duplicateWords = 0;
    int lineNumber = 0;

    while (fgets(line, sizeof(line), file)) {
        lineNumber++;
        trimWhitespace(line);

        if (strlen(line) == 0) continue; // Skip empty lines

        // Tokenize line using pipe '|'
        char *word = strtok(line, "|");
        char *pos = strtok(NULL, "|");
        char *def = strtok(NULL, "|");
        char *example = strtok(NULL, "|");

        if (word && pos && def && example) {
            trimWhitespace(word);
            trimWhitespace(pos);
            trimWhitespace(def);
            trimWhitespace(example);

            if (addWord(dictionary, word, pos, def, example)) {
                validEntries++;
            } else {
                duplicateWords++;
            }
        } else {
            invalidLines++;
            printf("Warning: Invalid entry ignored at line %d.\n", lineNumber);
        }
    }

    fclose(file);

    printf("Dictionary loaded successfully.\n");
    printf("Valid entries loaded: %d\n", validEntries);
    printf("Invalid lines ignored: %d\n", invalidLines);
    printf("Duplicate words ignored: %d\n", duplicateWords);

    return 1;
}

int saveDictionaryToFile(const Dictionary *dictionary, const char *filename) {
    if (dictionary == NULL || filename == NULL) return 0;

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return 0;
    }

    for (size_t i = 0; i < dictionary->bucketCount; i++) {
        DictionaryEntry *current = dictionary->buckets[i];
        while (current != NULL) {
            fprintf(file, "%s|%s|%s|%s\n", 
                    current->word, 
                    current->partOfSpeech, 
                    current->definition, 
                    current->exampleSentence);
            current = current->next;
        }
    }

    fclose(file);
    printf("Dictionary saved successfully to %s.\n", filename);
    return 1;
}