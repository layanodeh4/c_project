#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/dictionary.h"

char *duplicateString(const char *source){
    
    if (source == NULL){
        return NULL;
    }

    size_t length = strlen(source);
    char *copy = malloc((length + 1) * sizeof(char));

    if (copy == NULL){
        return NULL;
    }

    strcpy(copy, source);

    return copy;
}

Dictionary *createDictionary(size_t bucketCount){

    if (bucketCount == 0){
        return NULL;
    }

    Dictionary *dictionary = malloc(sizeof(Dictionary));

    if (dictionary == NULL){
        return NULL;
    }

    dictionary->buckets = malloc(bucketCount * sizeof(DictionaryEntry *));

    if (dictionary->buckets == NULL){
        free(dictionary);
        return NULL;

    }

    dictionary->bucketCount = bucketCount;
    dictionary->entryCount = 0;

    size_t i;

    for (i = 0; i < bucketCount; i++){
        dictionary->buckets[i] = NULL;
    }

    return dictionary;
}

size_t hashWord(const char *word, size_t bucketCount){

    if (word == NULL || bucketCount == 0){
        return 0;
    }
    
    size_t i;
    size_t hash = 0;
    for (i = 0; word[i] != '\0'; i++){
        hash = (hash * 31 + (unsigned char)tolower((unsigned char)word[i])) % bucketCount;
    }

    return hash;
}

DictionaryEntry *findWord(const Dictionary *dictionary, const char *word){

    if (dictionary == NULL || word == NULL){
        return NULL;
    }

    size_t index = hashWord(word, dictionary->bucketCount);
    DictionaryEntry *current = dictionary->buckets[index];

    while (current != NULL){

        size_t i = 0;
        int same = 1;

        while (current->word[i] != '\0' || word[i] != '\0'){

            if (tolower((unsigned char)current->word[i]) != tolower((unsigned char)word[i])){
                same = 0;
                break;
            }

            i++;
        }

        if (same){
            return current;
        }

        current = current->next;
    }

    return NULL;
}


int addWord(
    Dictionary *dictionary,
    const char *word,
    const char *partOfSpeech,  
    const char *definition,
    const char *exampleSentence
)
{

    if (dictionary == NULL ||
        word == NULL ||
        partOfSpeech == NULL ||
        definition == NULL ||
        exampleSentence == NULL)
    {
        return 0;
    }

    if (word[0] == '\0' ||
        partOfSpeech[0] == '\0' ||
        definition[0] == '\0' ||
        exampleSentence[0] == '\0')
    {
        return 0;
    }

    if (findWord(dictionary, word) != NULL){
        return 0;
    }

    DictionaryEntry *entry = malloc(sizeof(DictionaryEntry));

    if (entry == NULL){
        return 0;
    }

    entry->word = duplicateString(word);

    if (entry->word == NULL){
        free(entry);
        return 0;
    }

    entry->partOfSpeech = duplicateString(partOfSpeech);

    if (entry->partOfSpeech == NULL){
        free(entry->word);
        free(entry);
        return 0;
    }

    entry->definition = duplicateString(definition);

    if (entry->definition == NULL){
        free(entry->partOfSpeech);
        free(entry->word);
        free(entry);
        return 0;
    }

    entry->exampleSentence = duplicateString(exampleSentence);

    if (entry->exampleSentence == NULL){

        free(entry->definition);
        free(entry->partOfSpeech);
        free(entry->word);
        free(entry);
        return 0;
    }

    size_t index = hashWord(word, dictionary->bucketCount);
    entry->next = dictionary->buckets[index];
    dictionary->buckets[index] = entry;
    dictionary->entryCount++;

    return 1;
}


int deleteWord(Dictionary *dictionary, const char *word){

    if (dictionary == NULL || word == NULL){
        return 0;
    }
 
    size_t index = hashWord(word, dictionary->bucketCount);
    DictionaryEntry *current = dictionary->buckets[index];
    DictionaryEntry *previous = NULL;

    while (current != NULL){
        size_t i = 0;
        int same = 1;

        while (current->word[i] != '\0' || word[i] != '\0'){
            if (tolower((unsigned char)current->word[i]) != tolower((unsigned char)word[i])){
                same = 0;
                break;
            }

            i++;
        }

        if (same){
            if (previous == NULL){
                dictionary->buckets[index] = current->next;
            }
            else{
                previous->next = current->next;
            }

            free(current->word);
            free(current->definition);
            free(current->partOfSpeech);
            free(current->exampleSentence);
            free(current);

            dictionary->entryCount--;

            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}


void destroyDictionary(Dictionary *dictionary){

    if (dictionary == NULL){
        return;
    }

    size_t i;
    for (i = 0; i < dictionary->bucketCount; i++){
        DictionaryEntry *current = dictionary->buckets[i];

        while (current != NULL){
            DictionaryEntry *next = current->next;

            free(current->word);
            free(current->definition);
            free(current->partOfSpeech);
            free(current->exampleSentence);
            free(current);

            current = next;
        }
    }

    free(dictionary->buckets);
    free(dictionary);
}