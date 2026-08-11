#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "file_manager.h"
#include "input.h"
#include "statistics.h"

#define BUCKET_COUNT 503

void printMenu() {
    printf("\n============================================\n");
    printf("          LEXICORE ENGLISH DICTIONARY       \n");
    printf("============================================\n");
    printf("1. Load dictionary from file\n");
    printf("2. Search for an exact word\n");
    printf("3. Add a new word\n");
    printf("4. Delete a word\n");
    printf("5. Display dictionary statistics\n");
    printf("6. Save dictionary to file\n");
    printf("0. Save and exit\n");
    printf("============================================\n");
}

int main() {
    Dictionary *dict = createDictionary(BUCKET_COUNT);
    if (!dict) {
        fprintf(stderr, "Failed to initialize dictionary.\n");
        return 1;
    }

    int choice;
    char buffer[256];

    do {
        printMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                readString("Enter filename to load (e.g., data/dictionary.txt): ", buffer, sizeof(buffer));
                loadDictionaryFromFile(dict, buffer);
                break;
            case 2: {
                readString("Enter word to search: ", buffer, sizeof(buffer));
                DictionaryEntry *entry = findWord(dict, buffer);
                if (entry) {
                    printf("\nWord: %s\nPart of Speech: %s\nDefinition: %s\nExample: %s\n",
                           entry->word, entry->partOfSpeech, entry->definition, entry->exampleSentence);
                } else {
                    printf("Word '%s' not found.\n", buffer);
                }
                break;
            }
            case 3: {
                char word[128], pos[64], def[512], ex[512];
                readString("Enter word: ", word, sizeof(word));
                readString("Enter part of speech: ", pos, sizeof(pos));
                readString("Enter definition: ", def, sizeof(def));
                readString("Enter example sentence: ", ex, sizeof(ex));

                if (addWord(dict, word, pos, def, ex)) {
                    printf("Word added successfully.\n");
                } else {
                    printf("Failed to add word (word might already exist or invalid input).\n");
                }
                break;
            }
            case 4:
                readString("Enter word to delete: ", buffer, sizeof(buffer));
                if (deleteWord(dict, buffer)) {
                    printf("Word deleted successfully.\n");
                } else {
                    printf("Word not found.\n");
                }
                break;
            case 5:
                displayStatistics(dict);
                break;
            case 6:
                readString("Enter filename to save: ", buffer, sizeof(buffer));
                saveDictionaryToFile(dict, buffer);
                break;
            case 0:
                printf("Freeing resources and exiting...\n");
                destroyDictionary(dict);
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}