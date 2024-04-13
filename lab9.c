#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
};

// Node structure to handle chaining, defined within HashType
struct Node {
    struct RecordType data;
    struct Node* next;
};

// Fill out this structure
struct HashType {
    struct Node** buckets; // Array of pointers to Node for chaining
    int size;              // Size of the hash table
};

// Compute the hash function
int hash(int x) {
    int hashSize = 23;  // Example hash table size, should ideally be defined elsewhere or dynamically set
    return x % hashSize;
}

// Parses input file to an integer array
int parseData(char* input_lab_9, struct RecordType** ppData) {
    FILE* inFile = fopen(input_lab_9, "r");
    int dataSz = 0;
    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            fclose(inFile);
            exit(-1);
        }
        for (int i = 0; i < dataSz; ++i) {
            fscanf(inFile, "%d %c %d", &((*ppData)[i].id), &((*ppData)[i].name), &((*ppData)[i].order));
        }
        fclose(inFile);
    }
    return dataSz;
}

// Insert a record into the hash table with chaining
// Insert a record into the hash table with chaining (appending to maintain insertion order)
void insertRecord(struct HashType* ht, struct RecordType* record) {
    int idx = hash(record->id);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Failed to allocate memory for new node\n");
        exit(-1);
    }
    newNode->data = *record;  // Copy record data into node
    newNode->next = NULL;

    if (ht->buckets[idx] == NULL) {
        // First node in this bucket
        ht->buckets[idx] = newNode;
    } else {
        // Append to the end of the list to maintain insertion order
        struct Node* current = ht->buckets[idx];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


// Display records in the hash structure with chaining
// Display records in the hash structure with chaining, omitting empty (NULL) indices
void displayRecordsInHash(struct HashType* ht) {
    for (int i = 0; i < ht->size; ++i) {
        struct Node* current = ht->buckets[i];
        if (current != NULL) {  // Only print indices with non-null entries
            printf("index %d -> ", i);
            while (current != NULL) {
                printf("%d, %c, %d", current->data.id, current->data.name, current->data.order);
                current = current->next;
                if (current != NULL) {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
    }
}


int main(void) {
    struct RecordType* pRecords = NULL;
    int recordSz = parseData("input_lab_9.txt", &pRecords);
    struct HashType hashTable;
    hashTable.size = 23; // Define the size of hash table
    hashTable.buckets = (struct Node**)malloc(sizeof(struct Node*) * hashTable.size);
    for (int i = 0; i < hashTable.size; ++i) {
        hashTable.buckets[i] = NULL; // Initialize hash table
    }

    for (int i = 0; i < recordSz; ++i) {
        insertRecord(&hashTable, &pRecords[i]);  // Insert records into hash table
    }

    displayRecordsInHash(&hashTable); // Display hash table contents

    // Free allocated resources
    for (int i = 0; i < hashTable.size; ++i) {
        struct Node* current = hashTable.buckets[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable.buckets);
    free(pRecords);

    return 0;
}