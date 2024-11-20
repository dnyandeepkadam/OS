#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 5  // Maximum size of the buffer

// Shared buffer and variables
int buffer[MAX_BUFFER_SIZE];
int in = 0;  // Index where the producer will place data
int out = 0; // Index where the consumer will take data

// Semaphores for synchronization
sem_t mutex;  // Semaphore to ensure mutual exclusion
sem_t empty;   // Semaphore to track empty slots in buffer
sem_t full;    // Semaphore to track full slots in buffer

// Producer function: Produces data and places it in the buffer
void *producer(void *arg) {
    int item;
    
    while (1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);  // Decrement empty slots semaphore
        sem_wait(&mutex);  // Lock the buffer (mutual exclusion)

        // Place the item in the buffer
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % MAX_BUFFER_SIZE;

        sem_post(&mutex);  // Unlock the buffer
        sem_post(&full);   // Increment full slots semaphore

        sleep(1);  // Simulate some delay in production
    }
}

// Consumer function: Consumes data from the buffer
void *consumer(void *arg) {
    int item;
    
    while (1) {
        sem_wait(&full);  // Decrement full slots semaphore
        sem_wait(&mutex);  // Lock the buffer (mutual exclusion)

        // Take the item from the buffer
        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % MAX_BUFFER_SIZE;

        sem_post(&mutex);  // Unlock the buffer
        sem_post(&empty);  // Increment empty slots semaphore

        sleep(2);  // Simulate some delay in consumption
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);  // Mutex initialized to 1 (binary semaphore)
    sem_init(&empty, 0, MAX_BUFFER_SIZE);  // Empty initialized to buffer size
    sem_init(&full, 0, 0);  // Full initialized to 0, as buffer is empty initially

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (although they will run indefinitely in this example)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}