#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "statistics.h"

void displayStatistics(const Dictionary *dictionary) {
    if (dictionary == NULL) {
        printf("Dictionary is not initialized.\n");
        return;
    }

    size_t usedBuckets = 0;
    size_t emptyBuckets = 0;
    size_t longestChain = 0;
    size_t nouns = 0, verbs = 0, adjectives = 0, adverbs = 0, others = 0;

    for (size_t i = 0; i < dictionary->bucketCount; i++) {
        DictionaryEntry *current = dictionary->buckets[i];
        if (current == NULL) {
            emptyBuckets++;
        } else {
            usedBuckets++;
            size_t chainLength = 0;
            while (current != NULL) {
                chainLength++;

                // Categorize part of speech
                if (current->partOfSpeech) {
                    if (strcasecmp(current->partOfSpeech, "noun") == 0) nouns++;
                    else if (strcasecmp(current->partOfSpeech, "verb") == 0) verbs++;
                    else if (strcasecmp(current->partOfSpeech, "adjective") == 0) adjectives++;
                    else if (strcasecmp(current->partOfSpeech, "adverb") == 0) adverbs++;
                    else others++;
                }

                current = current->next;
            }
            if (chainLength > longestChain) {
                longestChain = chainLength;
            }
        }
    }

    double loadFactor = (double)dictionary->entryCount / dictionary->bucketCount;
    double avgChainLength = usedBuckets > 0 ? (double)dictionary->entryCount / usedBuckets : 0;

    printf("\n========== Dictionary Statistics ==========\n");
    printf("Total entries:                 %zu\n", dictionary->entryCount);
    printf("Total buckets:                 %zu\n", dictionary->bucketCount);
    printf("Used buckets:                  %zu\n", usedBuckets);
    printf("Empty buckets:                 %zu\n", emptyBuckets);
    printf("Load factor:                   %.2f\n", loadFactor);
    printf("Longest chain:                 %zu\n", longestChain);
    printf("Average used-chain length:     %.2f\n", avgChainLength);
    printf("-------------------------------------------\n");
    printf("Nouns: %zu | Verbs: %zu | Adjectives: %zu | Adverbs: %zu | Others: %zu\n", 
           nouns, verbs, adjectives, adverbs, others);
    printf("===========================================\n\n");
}