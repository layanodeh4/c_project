#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

unsigned long hashFunction(const char *str, size_t bucketCount) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + tolower(c);
    }
    return bucketCount ? (hash % bucketCount) : 0;
}

Dictionary* createDictionary(size_t bucketCount) {
    if (bucketCount == 0) bucketCount = INITIAL_BUCKET_COUNT;

    Dictionary *dict = (Dictionary*) malloc(sizeof(Dictionary));
    if (!dict) return NULL;

    dict->buckets = (DictionaryEntry**) calloc(bucketCount, sizeof(DictionaryEntry*));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }

    dict->bucketCount = bucketCount;
    dict->entryCount = 0;
    return dict;
}

int addWord(Dictionary *dict, const char *word, const char *pos, const char *def, const char *example) {
    if (!dict || !word || !pos || !def || !example) return 0;

    if (findWord(dict, word) != NULL) return 0;

    unsigned long index = hashFunction(word, dict->bucketCount);

    DictionaryEntry *newEntry = (DictionaryEntry*) malloc(sizeof(DictionaryEntry));
    if (!newEntry) return 0;

    strncpy(newEntry->word, word, MAX_WORD_LEN - 1);
    newEntry->word[MAX_WORD_LEN - 1] = '\0';

    strncpy(newEntry->partOfSpeech, pos, MAX_POS_LEN - 1);
    newEntry->partOfSpeech[MAX_POS_LEN - 1] = '\0';

    strncpy(newEntry->definition, def, MAX_DEF_LEN - 1);
    newEntry->definition[MAX_DEF_LEN - 1] = '\0';

    strncpy(newEntry->exampleSentence, example, MAX_EX_LEN - 1);
    newEntry->exampleSentence[MAX_EX_LEN - 1] = '\0';

    newEntry->next = dict->buckets[index];
    dict->buckets[index] = newEntry;
    dict->entryCount++;

    return 1;
}

DictionaryEntry* findWord(const Dictionary *dict, const char *word) {
    if (!dict || !word) return NULL;

    unsigned long index = hashFunction(word, dict->bucketCount);
    DictionaryEntry *current = dict->buckets[index];

    while (current) {
        if (strcasecmp(current->word, word) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int deleteWord(Dictionary *dict, const char *word) {
    if (!dict || !word) return 0;

    unsigned long index = hashFunction(word, dict->bucketCount);
    DictionaryEntry *current = dict->buckets[index];
    DictionaryEntry *prev = NULL;

    while (current) {
        if (strcasecmp(current->word, word) == 0) {
            if (prev == NULL) {
                dict->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            dict->entryCount--;
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void destroyDictionary(Dictionary *dict) {
    if (!dict) return;

    for (size_t i = 0; i < dict->bucketCount; i++) {
        DictionaryEntry *current = dict->buckets[i];
        while (current) {
            DictionaryEntry *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(dict->buckets);
    free(dict);
}