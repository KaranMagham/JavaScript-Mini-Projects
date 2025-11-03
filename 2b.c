#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define MAX_THREADS 10
// Structure to hold thread data
typedef struct
{
    int start;
    int end;
} ThreadData;
// Function to check if a number is prime
int is_prime(int num)
{
    if (num < 2)
        return 0;
    if (num == 2)
        return 1;
    if (num % 2 == 0)
        return 0;
    for (int i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
// Thread function to find primes in a given range
void *find_primes(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start; i <= data->end; i++)
    {
        if (is_prime(i))
        {
            printf("Prime: %d\n", i);
        }
    }
    pthread_exit(NULL);
}
int main()
{
    int N, num_threads;
    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    // Input upper limit N
    printf("Enter the upper limit (N): ");
    scanf("%d", &N);
    if (N < 2)
    {
        printf("There are no primes less than 2.\n");
        return 0;
    }
    // Input number of threads
    printf("Enter number of threads (1-%d): ", MAX_THREADS);
    scanf("%d", &num_threads);
    if (num_threads < 1 || num_threads > MAX_THREADS)
    {
        printf("Invalid number of threads.\n");
        return 1;
    }
    // Divide the range among threads
    int range = (N - 1) / num_threads; // start from 2 to N
    int start = 2;
    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].start = start;
        thread_data[i].end = (i == num_threads - 1) ? N : start + range - 1;
        start = thread_data[i].end + 1;
        pthread_create(&threads[i], NULL, find_primes,
                       (void *)&thread_data[i]);
    }
    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}