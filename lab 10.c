#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode {
    int count; // to store the number of occurrences of a word
    struct TrieNode* children[26]; // array for each letter of the alphabet
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Function to create a new Trie node
struct TrieNode* createTrieNode(void) {
    struct TrieNode *newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    newNode->count = 0;
    for (int i = 0; i < 26; i++)
        newNode->children[i] = NULL;
    return newNode;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie*)malloc(sizeof(struct Trie));
    if (!trie) return NULL;
    trie->root = createTrieNode();
    return trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *trie, char *word) {
    struct TrieNode *pCrawl = trie->root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createTrieNode();
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *trie, char *word) {
    struct TrieNode *pCrawl = trie->root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
            return 0;
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->count;
}

// Deallocates the trie nodes recursively
void deallocateNodes(struct TrieNode *node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        if (node->children[i])
            deallocateNodes(node->children[i]);
    }
    free(node);
}

// Deallocate the trie structure
void deallocateTrie(struct Trie *trie) {
    if (!trie) return;
    deallocateNodes(trie->root);
    free(trie);
}

// Assuming readDictionary is correctly implemented elsewhere
// This function reads words from a file named `filename` and fills them into `pInWords`, returning the count of words.

int main(void) {
    struct Trie *trie = createTrie();
    char *words[] = {"not", "note", "ucf", "notaword", "notawordeither", "notaword", "ucf", "note", "ucf", "notawordeithereither", "not", "ucf"};
    int numWords = sizeof(words) / sizeof(words[0]);

    // Insert all words into the Trie
    for (int i = 0; i < numWords; i++) {
        insert(trie, words[i]);
    }

    // Query the Trie
    char *queryWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numQueries = sizeof(queryWords) / sizeof(queryWords[0]);
    for (int i = 0; i < numQueries; i++) {
        printf("%s : %d\n", queryWords[i], numberOfOccurances(trie, queryWords[i]));
    }

    // Clean up
    deallocateTrie(trie);

    return 0;
}
