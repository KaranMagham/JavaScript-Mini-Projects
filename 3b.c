#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;      // For protecting shared variables
pthread_mutex_t write_lock; // For writers to get exclusive access
int read_count = 0;         // Number of active readers
// Shared resource
int shared_data = 0;
void *reader(void *arg)
{
    int id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1)
    {
        // First reader locks writers out
        pthread_mutex_lock(&write_lock);
    }
    pthread_mutex_unlock(&mutex);
    // Reading (simulated)
    printf("Reader %d: reading shared_data = %d\n", id, shared_data);
    sleep(1); // Simulate read time
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0)
    {
        // Last reader unlocks writers
        pthread_mutex_unlock(&write_lock);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
void *writer(void *arg)
{
    int id = *((int *)arg);
    pthread_mutex_lock(&write_lock);
    // Writing (simulated)
    shared_data += 10;
    printf("Writer %d: writing shared_data = %d\n", id, shared_data);
    sleep(1); // Simulate write time
    pthread_mutex_unlock(&write_lock);
    pthread_exit(NULL);
}
int main()
{
    pthread_t readers[5], writers[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};
    // Initialize mutexes
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&write_lock, NULL);
    // Create reader and writer threads
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    sleep(1);
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    sleep(1);
    pthread_create(&readers[1], NULL, reader, &reader_ids[1]);
    pthread_create(&readers[2], NULL, reader, &reader_ids[2]);
    sleep(1);
    pthread_create(&writers[1], NULL, writer, &writer_ids[1]);
    pthread_create(&readers[3], NULL, reader, &reader_ids[3]);
    pthread_create(&readers[4], NULL, reader, &reader_ids[4]);
    // Wait for all threads to finish
    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);
    // Destroy mutexes
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_lock);
    return 0;
}