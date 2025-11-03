#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char song[100];
    struct Node *next;
};

// Add song to the playlist
struct Node* addSong(struct Node *head, char songName[]) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->song, songName);
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

// Delete a song from the playlist
struct Node* deleteSong(struct Node *head, char songName[]) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return head;
    }

    struct Node *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->song, songName) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song not found in playlist.\n");
        return head;
    }

    if (prev == NULL)
        head = head->next;
    else
        prev->next = temp->next;

    printf("Deleted '%s' from the playlist.\n", songName);
    free(temp);
    return head;
}

// Display playlist
void display(struct Node *head) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    printf("\nYour Playlist:\n");
    while (head != NULL) {
        printf("%s\n", head->song);
        head = head->next;
    }
}

// Free entire playlist
void freeList(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node *playlist = NULL;
    int choice;
    char songName[100];

    do {
        printf("\n--- Playlist Menu ---\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Display Playlist\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume newline

        switch (choice) {
            case 1:
                printf("Enter song name: ");
                fgets(songName, 100, stdin);
                songName[strcspn(songName, "\n")] = '\0'; // remove newline
                playlist = addSong(playlist, songName);
                printf("Song added successfully!\n");
                break;

            case 2:
                printf("Enter song name to delete: ");
                fgets(songName, 100, stdin);
                songName[strcspn(songName, "\n")] = '\0';
                playlist = deleteSong(playlist, songName);
                break;

            case 3:
                display(playlist);
                break;

            case 4:
                freeList(playlist);
                printf("Exiting... All memory freed.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
