#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_ITERATIONS 20

int counter = 0;      // Shared resource
pthread_mutex_t lock; // Mutex for protecting access

void *increment_counter(void *arg)
{
  for (int i = 0; i < NUM_ITERATIONS; ++i)
  {
    pthread_mutex_lock(&lock);   // Acquire the lock
    counter++;                   // Critical section
    pthread_mutex_unlock(&lock); // Release the lock
  }
  return NULL;
}

int main()
{
  pthread_t threads[NUM_THREADS];

  // Initialize the mutex before using it
  pthread_mutex_init(&lock, NULL);

  // Create threads
  for (int i = 0; i < NUM_THREADS; ++i)
    pthread_create(&threads[i], NULL, increment_counter, NULL);

  // Wait for threads to finish
  for (int i = 0; i < NUM_THREADS; ++i)
    pthread_join(threads[i], NULL);

  // Destroy the mutex
  pthread_mutex_destroy(&lock);

  // Print final counter value
  printf("Final counter value: %d\n", counter); // Should be NUM_THREADS * NUM_ITERATIONS

  return 0;
}
