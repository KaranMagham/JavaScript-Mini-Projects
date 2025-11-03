#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_THREADS 10
// Global sum and mutex
long long global_sum = 0;
pthread_mutex_t sum_mutex;
// Structure for thread parameters
typedef struct
{
    int start;
    int end;
} ThreadData;
// Thread function
void *partial_sum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    long long local_sum = 0;
    for (int i = data->start; i <= data->end; i++)
    {
        local_sum += i;
    }
    // Lock before updating global sum
    pthread_mutex_lock(&sum_mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&sum_mutex);
    pthread_exit(NULL);
}
int main()
{
    int N, num_threads;
    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    // Input N
    printf("Enter a non-negative integer N: ");
    scanf("%d", &N);
    if (N < 0)
    {
        printf("Error: N must be non-negative.\n");
        return 1;
    }
    // Input number of threads
    printf("Enter number of threads (1-%d): ", MAX_THREADS);
    scanf("%d", &num_threads);
    if (num_threads < 1 || num_threads > MAX_THREADS)
    {
        printf("Error: Invalid number of threads.\n");
        return 1;
    }
    // Initialize mutex
    pthread_mutex_init(&sum_mutex, NULL);
    // Calculate range for each thread
    int chunk_size = (N + 1) / num_threads;
    int remainder = (N + 1) % num_threads;
    int start = 0;
    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].start = start;
        thread_data[i].end = start + chunk_size - 1;
        if (remainder > 0)
        {
            thread_data[i].end++;
            remainder--;
        }
        start = thread_data[i].end + 1;
        pthread_create(&threads[i], NULL, partial_sum, (void *)&thread_data[i]);
    }
    // Join threads
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    // Destroy mutex
    pthread_mutex_destroy(&sum_mutex);
    // Print result
    printf("Sum of 0 to %d = %lld\n", N, global_sum);
    return 0;
}