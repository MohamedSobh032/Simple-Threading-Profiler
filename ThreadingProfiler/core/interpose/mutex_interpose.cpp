#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>

thread_local int counter = 0;

static int (*real_pthread_mutex_lock)(pthread_mutex_t*) = NULL;
static int (*real_pthread_mutex_unlock)(pthread_mutex_t*) = NULL;

int
pthread_mutex_lock(pthread_mutex_t* mutex)
{
  if (!real_pthread_mutex_lock)
    real_pthread_mutex_lock = (int (*)(pthread_mutex_t*))dlsym(RTLD_NEXT, "pthread_mutex_lock");

  fprintf(stderr, "[PROFILER] pthread_mutex_lock called\n");

  int result = real_pthread_mutex_lock(mutex);

  fprintf(stderr, "[PROFILER] pthread_mutex_lock returned %d %d\n", result, counter++);
  return result;
}

int
pthread_mutex_unlock(pthread_mutex_t* mutex)
{
  if (!real_pthread_mutex_unlock)
    real_pthread_mutex_unlock = (int (*)(pthread_mutex_t*))dlsym(RTLD_NEXT, "pthread_mutex_unlock");

  fprintf(stderr, "[PROFILER] pthread_mutex_unlock called\n");

  int result = real_pthread_mutex_unlock(mutex);

  fprintf(stderr, "[PROFILER] pthread_mutex_unlock returned %d\n", result);
  return result;
}