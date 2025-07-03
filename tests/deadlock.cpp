#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1_func(void *arg)
{
  pthread_mutex_lock(&mtx1);
  printf("Thread 1 acquired mtx1\n");
  sleep(1);  // encourage overlap
  pthread_mutex_lock(&mtx2);
  printf("Thread 1 acquired mtx2\n");

  pthread_mutex_unlock(&mtx2);
  pthread_mutex_unlock(&mtx1);
  return NULL;
}

void *thread2_func(void *arg)
{
  pthread_mutex_lock(&mtx2);
  printf("Thread 2 acquired mtx2\n");
  sleep(1);  // encourage overlap
  pthread_mutex_lock(&mtx1);
  printf("Thread 2 acquired mtx1\n");

  pthread_mutex_unlock(&mtx1);
  pthread_mutex_unlock(&mtx2);
  return NULL;
}

int main()
{
  pthread_t t1, t2;
  pthread_create(&t1, NULL, thread1_func, NULL);
  pthread_create(&t2, NULL, thread2_func, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Finished\n");
  return 0;
}
