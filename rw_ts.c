#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_READERS 5
#define MAX_WRITERS 2

sem_t mutex;          // Semaphore for read_count protection
sem_t write_mutex;    // Semaphore for write access control
int shared_data = 0;  // Shared data to be read/written
int read_count = 0;   // Number of active readers

// Function for reading the shared data
void *reader(void *arg) {
    int reader_id = *((int *)arg);

    // Reader trying to access the shared data
    sem_wait(&mutex);   // Lock mutex to update read_count
    read_count++;
    if (read_count == 1) {
        sem_wait(&write_mutex);  // First reader locks the writer mutex
    }
    sem_post(&mutex);   // Unlock mutex

    printf("Reader %d: Read shared data = %d\n", reader_id, shared_data);
    sleep(1);  // Simulate reading time

    // Reader releasing the lock
    sem_wait(&mutex);   // Lock mutex to update read_count
    read_count--;
    if (read_count == 0) {
        sem_post(&write_mutex);  // Last reader releases the write_mutex
    }
    sem_post(&mutex);   // Unlock mutex

    return NULL;
}

// Function for writing to the shared data
void *writer(void *arg) {
    int writer_id = *((int *)arg);

    // Writer needs exclusive access
    sem_wait(&write_mutex);   // Lock write_mutex to ensure exclusive access
    shared_data = rand() % 100;  // Simulate writing (new random value)
    printf("Writer %d: Written new data = %d\n", writer_id, shared_data);
    sem_post(&write_mutex);   // Unlock write_mutex

    sleep(1);  // Simulate writing time

    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int reader_ids[MAX_READERS], writer_ids[MAX_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);       // Initialize mutex to 1 (binary semaphore)
    sem_init(&write_mutex, 0, 1); // Initialize write_mutex to 1 (binary semaphore)

    // Creating reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;  // Assign reader IDs
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Creating writer threads
    for (int i = 0; i < MAX_WRITERS; i++) {
        writer_ids[i] = i + 1;  // Assign writer IDs
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Wait for all reader and writer threads to finish
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);

    return 0;
}
// gcc -o reader_writer reader_writer.c -pthread
//./reader_writer