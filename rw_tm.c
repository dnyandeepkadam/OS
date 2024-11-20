#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READERS 5
#define MAX_WRITERS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex to control access to shared data
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex to ensure exclusive write access
int shared_data = 0; // Shared data to be read/written
int read_count = 0; // Counter for the number of active readers

// Function for reading the shared data
void *reader(void *arg) {
    int reader_id = *((int *)arg);

    // Reader trying to access the shared data
    pthread_mutex_lock(&mutex); // Access control for read count
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&write_mutex); // First reader locks the writer mutex to prevent writing
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d: Read shared data = %d\n", reader_id, shared_data);
    sleep(1); // Simulate reading time

    // Reader releasing the lock
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&write_mutex); // Last reader releases the writer lock
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Function for writing to the shared data
void *writer(void *arg) {
    int writer_id = *((int *)arg);

    // Writer needs exclusive access
    pthread_mutex_lock(&write_mutex);
    shared_data = rand() % 100; // Simulate writing (new random value)
    printf("Writer %d: Written new data = %d\n", writer_id, shared_data);
    pthread_mutex_unlock(&write_mutex);

    sleep(1); // Simulate writing time

    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int reader_ids[MAX_READERS], writer_ids[MAX_WRITERS];

    // Creating reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1; // Assign reader IDs
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Creating writer threads
    for (int i = 0; i < MAX_WRITERS; i++) {
        writer_ids[i] = i + 1; // Assign writer IDs
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Wait for all reader and writer threads to finish
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}

// gcc -o reader_writer reader_writer.c -pthread
//./reader_writer