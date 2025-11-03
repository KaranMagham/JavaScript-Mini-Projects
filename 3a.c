#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define BUFFER_SIZE 5
#define PRODUCE_COUNT 10
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;
pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;
// Producer thread function
void *producer(void *arg)
{
    for (int i = 0; i < PRODUCE_COUNT; i++)
    {
        int item = i + 1;
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE)
        {
            // Buffer is full, wait for not_full signal
            pthread_cond_wait(&not_full, &mutex);
        }
        // Add item to buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;
        // Signal that buffer is not empty
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        sleep(1); // simulate production delay
    }
    pthread_exit(NULL);
}
// Consumer thread function
void *consumer(void *arg)
{
    for (int i = 0; i < PRODUCE_COUNT; i++)
    {
        pthread_mutex_lock(&mutex);
        while (count == 0)
        {
            // Buffer is empty, wait for not_empty signal
            pthread_cond_wait(&not_empty, &mutex);
        }
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;
        // Signal that buffer is not full
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        sleep(1); // simulate consumption delay
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t prod_thread, cons_thread;
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);
    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    // Wait for both threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    // Destroy synchronization primitives
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    return 0;
}