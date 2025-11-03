#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int adj[MAX][MAX];
int visited[MAX];
int n; // number of vertices

// Function to create graph using adjacency matrix
void createGraph() {
    int i, j;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
}

// BFS using queue
void BFS(int start) {
    int queue[MAX], front = -1, rear = -1;
    int i;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[++rear] = start;
    front = 0;

    printf("BFS Traversal: ");

    while (front <= rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (i = 0; i < n; i++) {
            if (adj[current][i] == 1 && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// DFS using recursion
void DFS(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);

    for (i = 0; i < n; i++) {
        if (adj[v][i] == 1 && visited[i] == 0)
            DFS(i);
    }
}

void DFS_traversal(int start) {
    int i;
    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("DFS Traversal: ");
    DFS(start);
    printf("\n");
}

int main() {
    int choice, start;

    createGraph();

    do {
        printf("\n--- Graph Menu ---\n");
        printf("1. Display Adjacency Matrix\n");
        printf("2. BFS Traversal\n");
        printf("3. DFS Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAdjacency Matrix:\n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++)
                        printf("%d ", adj[i][j]);
                    printf("\n");
                }
                break;

            case 2:
                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);
                BFS(start);
                break;

            case 3:
                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);
                DFS_traversal(start);
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
