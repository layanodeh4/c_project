#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayMenu();
int getValidatedChoice(int min, int max);
void editWord();
void displayAlphabetically();
void reloadDictionary();
void saveBeforeExit();

int main() {
    int choice;
    
    do {
        displayMenu();
        choice = getValidatedChoice(1, 6);
        
        switch (choice) {
            case 1:
                editWord();
                break;
            case 2:
              displayAlphabetically();
                break;
            case 3:
                reloadDictionary();
                break;
            case 4:
                saveBeforeExit();
                break;
            case 5:
                printf("Saving and exiting program...\n");
                saveBeforeExit();
                break;
            case 6:
                printf("Exiting without saving...\n");
                break;
        }
    } 
while (choice != 5 && choice != 6);

    return 0;
}

void displayMenu() {
    printf("\n--- Dictionary Menu ---\n");

    printf("1. Edit Word\n");

    printf("2. Display Alphabetically\n");

    printf("3. Reload Dictionary\n");

    printf("4. Save Before Exit (Manual Save)\n");

    printf("5. Exit (Save & Quit)\n");

    printf("6. Exit (Quit Without Saving)\n");

}

int getValidatedChoice(int min, int max) {
    int choice;
    char buffer[100];
    
    while (1) {
        printf("Enter your choice (%d-%d): ", min, max);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL){
            if (sscanf(buffer, "%d", &choice) == 1) {
                if (choice >= min && choice <= max) {
                    return choice;
                }
            }
        }

        printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
    }
}

void editWord() {
    char word[50];
    printf("\n[Interface] Enter the word you want to edit: ");

    if (scanf("%s", word) == 1) {

        while (getchar() != '\n');

        printf("Editing word: %s (Functionality linked to backend)\n", word);

    }
}

void displayAlphabetically() {
    printf("\n[Interface] Displaying dictionary words in alphabetical order...\n");
}

void reloadDictionary() {
    printf("\n[Interface] Reloading dictionary from file...\n");
}

void saveBeforeExit() {
    printf("\n[Interface] Saving current dictionary state to file...\n");
}