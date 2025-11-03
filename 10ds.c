#include <stdio.h>
#define SIZE 10

int hashTable[SIZE];

// Initialize hash table
void init() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
}

// Hash function
int hash(int key) {
    return key % SIZE;
}

// Insert key into hash table
void insert(int key) {
    int index = hash(key);
    int i = 0;

    while (hashTable[(index + i) % SIZE] != -1 && i < SIZE)
        i++;

    if (i == SIZE) {
        printf("Hash table is full!\n");
        return;
    }

    hashTable[(index + i) % SIZE] = key;
    printf("Inserted %d at index %d\n", key, (index + i) % SIZE);
}

// Search for a key
void search(int key) {
    int index = hash(key);
    int i = 0;

    while (hashTable[(index + i) % SIZE] != -1 && i < SIZE) {
        if (hashTable[(index + i) % SIZE] == key) {
            printf("Found %d at index %d\n", key, (index + i) % SIZE);
            return;
        }
        i++;
    }
    printf("%d not found in hash table.\n", key);
}

// Delete a key
void deleteKey(int key) {
    int index = hash(key);
    int i = 0;

    while (hashTable[(index + i) % SIZE] != -1 && i < SIZE) {
        if (hashTable[(index + i) % SIZE] == key) {
            hashTable[(index + i) % SIZE] = -1;
            printf("Deleted %d from index %d\n", key, (index + i) % SIZE);
            return;
        }
        i++;
    }
    printf("%d not found, cannot delete.\n", key);
}

// Display hash table
void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < SIZE; i++)
        printf("[%d] → %d\n", i, hashTable[i]);
}

int main() {
    int choice, key;
    init();

    do {
        printf("\n--- Hash Table Menu ---\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

