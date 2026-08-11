#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stddef.h>

#define INITIAL_BUCKET_COUNT 101
#define MAX_WORD_LEN 64
#define MAX_POS_LEN 32
#define MAX_DEF_LEN 256
#define MAX_EX_LEN 256

typedef struct DictionaryEntry {
    char word[MAX_WORD_LEN];
    char partOfSpeech[MAX_POS_LEN];
    char definition[MAX_DEF_LEN];
    char exampleSentence[MAX_EX_LEN];
    struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct Dictionary {
    DictionaryEntry **buckets;
    size_t bucketCount;
    size_t entryCount;
} Dictionary;

/* Function Prototypes */
unsigned long hashFunction(const char *str, size_t bucketCount);
Dictionary* createDictionary(size_t bucketCount);
int addWord(Dictionary *dict, const char *word, const char *pos, const char *def, const char *example);
DictionaryEntry* findWord(const Dictionary *dict, const char *word);
int deleteWord(Dictionary *dict, const char *word);
void destroyDictionary(Dictionary *dict);

#endif /* DICTIONARY_H */