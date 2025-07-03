#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>

#include "../event/mutex_event.hpp"
#include "../profiler/profiler.hpp"
#include "../profiler_tls.hpp"

static int (*real_pthread_mutex_lock)(pthread_mutex_t*) = NULL;
static int (*real_pthread_mutex_unlock)(pthread_mutex_t*) = NULL;

int pthread_mutex_lock(pthread_mutex_t* mutex)
{
  if (!real_pthread_mutex_lock)
    real_pthread_mutex_lock = (int (*)(pthread_mutex_t*))dlsym(RTLD_NEXT, "pthread_mutex_lock");

  if (profiling_disabled) return real_pthread_mutex_lock(mutex);

  profiler::submit(std::make_unique<MutexEvent>(EventType::MUTEX_WAIT, mutex));

  int result = real_pthread_mutex_lock(mutex);

  if (result == 0) profiler::submit(std::make_unique<MutexEvent>(EventType::MUTEX_LOCK, mutex));

  return result;
}

int pthread_mutex_unlock(pthread_mutex_t* mutex)
{
  if (!real_pthread_mutex_unlock)
    real_pthread_mutex_unlock = (int (*)(pthread_mutex_t*))dlsym(RTLD_NEXT, "pthread_mutex_unlock");

  if (profiling_disabled) return real_pthread_mutex_unlock(mutex);

  profiler::submit(std::make_unique<MutexEvent>(EventType::MUTEX_UNLOCK, mutex));

  return real_pthread_mutex_unlock(mutex);
}