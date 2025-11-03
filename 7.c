#include <stdio.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10
int main()
{
    int n, m;                                // Number of processes and resources
    int alloc[MAX_PROCESSES][MAX_RESOURCES]; // Allocation matrix
    int max[MAX_PROCESSES][MAX_RESOURCES];   // Max matrix
    int need[MAX_PROCESSES][MAX_RESOURCES];  // Need matrix
    int avail[MAX_RESOURCES];                // Available vector
    int finish[MAX_PROCESSES] = {0};         // Finish array
    int safe_seq[MAX_PROCESSES];
    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    // Input Allocation matrix
    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    // Input Max matrix
    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    // Input Available resources
    printf("\nEnter Available resources: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }
    // Calculate Need matrix = Max - Allocation
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    // Banker's Algorithm to find safe sequence
    int count = 0;
    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                        break;
                }
                if (j == m)
                {
                    // Process can be satisfied
                    for (int k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("\nSystem is NOT in a safe state.\n");
            return 1;
        }
    }
    // Print the safe sequence
    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d", safe_seq[i]);
        if (i != n - 1)
            printf(" -> ");
    }
    printf("\n");
    return 0;
}
