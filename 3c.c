#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_CUSTOMERS 10
#define NUM_CHAIRS 3
// Mutex for critical section
pthread_mutex_t mutex;
// Condition variables
pthread_cond_t barber_ready;
pthread_cond_t customer_ready;
// Shared variables
int waiting_customers = 0;
int barber_sleeping = 1;
// Barber thread function
void *barber(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        // Wait if no customers
        while (waiting_customers == 0)
        {
            printf("Barber: No customers, going to sleep.\n");
            pthread_cond_wait(&customer_ready, &mutex);
        }
        // Serve next customer
        waiting_customers--;
        printf("Barber: Cutting hair. Waiting customers: %d\n",
               waiting_customers);
        pthread_cond_signal(&barber_ready); // Signal customer
        pthread_mutex_unlock(&mutex);
        // Simulate haircut
        sleep(2);
        printf("Barber: Done cutting hair.\n");
    }
    return NULL;
}
// Customer thread function
void *customer(void *arg)
{
    int id = *((int *)arg);
    free(arg);
    pthread_mutex_lock(&mutex);
    if (waiting_customers < NUM_CHAIRS)
    {
        waiting_customers++;
        printf("Customer %d: Waiting. Total waiting: %d\n", id,
               waiting_customers);
        pthread_cond_signal(&customer_ready);     // Wake barber
        pthread_cond_wait(&barber_ready, &mutex); // Wait for barber
        printf("Customer %d: Getting haircut.\n", id);
    }
    else
    {
        printf("Customer %d: No chair available, leaving.\n", id);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main()
{
    pthread_t barber_thread;
    pthread_t customer_threads[NUM_CUSTOMERS];
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&barber_ready, NULL);
    pthread_cond_init(&customer_ready, NULL);
    // Create barber thread
    pthread_create(&barber_thread, NULL, barber, NULL);
    // Create customer threads with random arrival
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        sleep(rand() % 3); // Random arrival time
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customer_threads[i], NULL, customer, id);
    }
    // Wait for all customer threads
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        pthread_join(customer_threads[i], NULL);
    }
    // Barber continues indefinitely; for demo, cancel thread
    printf("All customers have been processed.\n");
    pthread_cancel(barber_thread);
    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&barber_ready);
    pthread_cond_destroy(&customer_ready);
    return 0;
}