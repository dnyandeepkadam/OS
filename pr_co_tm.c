#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 5  // Maximum size of the buffer

// Shared buffer and variables
int buffer[MAX_BUFFER_SIZE];
int in = 0;  // Index where the producer will place data
int out = 0; // Index where the consumer will take data
pthread_mutex_t mutex;  // Mutex to protect buffer
pthread_cond_t empty, full;  // Condition variables for empty and full buffer

// Producer function: Produces data and places it in the buffer
void *producer(void *arg) {
    int item;
    
    while (1) {
        item = rand() % 100;  // Produce a random item
        pthread_mutex_lock(&mutex);  // Lock the buffer

        // Wait if the buffer is full
        while ((in + 1) % MAX_BUFFER_SIZE == out) {
            pthread_cond_wait(&full, &mutex);
        }

        // Place the item in the buffer
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % MAX_BUFFER_SIZE;

        // Signal that the buffer is no longer empty
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);  // Unlock the buffer

        sleep(1);  // Simulate some delay in production
    }
}

// Consumer function: Consumes data from the buffer
void *consumer(void *arg) {
    int item;
    
    while (1) {
        pthread_mutex_lock(&mutex);  // Lock the buffer

        // Wait if the buffer is empty
        while (in == out) {
            pthread_cond_wait(&empty, &mutex);
        }

        // Take the item from the buffer
        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % MAX_BUFFER_SIZE;

        // Signal that the buffer is no longer full
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);  // Unlock the buffer

        sleep(2);  // Simulate some delay in consumption
    }
}

int main() {
    pthread_t prod_thread, cons_thread;
    
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (although they will run indefinitely in this example)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;
}