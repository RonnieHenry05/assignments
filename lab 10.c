#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
    struct Trie *children[26];
    int occurrences;  // Number of occurrences of the word
};

struct Trie *createNode(void) {
    struct Trie *newNode = malloc(sizeof(struct Trie));
    if (!newNode) {
        return NULL; // Return NULL to handle failed memory allocation
    }
    newNode->occurrences = 0;
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    if (!pTrie) return;  // Ensure pTrie is not NULL before proceeding

    int length = strlen(word);
    struct Trie *pCrawl = pTrie;
    
    for (int level = 0; level < length; level++) {
        if (word[level] < 'a' || word[level] > 'z') {
            continue; // Skip invalid characters
        }
        int index = word[level] - 'a';

        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode();
            if (!pCrawl->children[index]) {
                return; 
            }
        }
        pCrawl = pCrawl->children[index];
    }
    
    pCrawl->occurrences++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (!pTrie) return 0;  // Return 0 if pTrie is NULL

    int length = strlen(word);
    struct Trie *pCrawl = pTrie;
    
    for (int level = 0; level < length; level++) {
        if (word[level] < 'a' || word[level] > 'z') {
            continue; // Handle invalid characters safely
        }
        int index = word[level] - 'a';

        if (!pCrawl->children[index]) {
            return 0; // The word is not in the trie
        }
        
        pCrawl = pCrawl->children[index];
    }
    
    return (pCrawl != NULL && pCrawl->occurrences) ? pCrawl->occurrences : 0;
}

// Deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i]) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}
// Initializes a trie structure
struct Trie *createTrie()
{return createNode(); // A trie is initialized by creating a new node
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        exit(EXIT_FAILURE);
    }

    char buffer[256]; // Buffer to hold each word
    int wordCount = 0;

    while (fgets(buffer, sizeof(buffer), file) && wordCount < 256) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        pInWords[wordCount++] = strdup(buffer); // Duplicate the string
    }

    fclose(file);
    return wordCount;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
    for (int i = 0; i < numWords; ++i) {
        free(inWords[i]);
    }

    return 0;
}
