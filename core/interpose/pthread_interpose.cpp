#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <memory>

#include "../event/thread_event.hpp"
#include "../profiler/profiler.hpp"
#include "../profiler_tls.hpp"

struct ThreadArgs
{
  void* (*start_routine)(void*);
  void* arg;
};

static int (*real_pthread_create)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*) = NULL;
static int (*real_pthread_join)(pthread_t, void**) = NULL;

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg)
{
  if (!real_pthread_create)
    real_pthread_create =
        (int (*)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*))dlsym(RTLD_NEXT, "pthread_create");

  if (profiling_disabled) return real_pthread_create(thread, attr, start_routine, arg);

  profiler::submit(std::make_unique<ThreadEvent>(EventType::THREAD_CREATE));
  auto wrapper = [](void* data)
  {
    ThreadArgs* args = static_cast<ThreadArgs*>(data);
    profiler::submit(std::make_unique<ThreadEvent>(EventType::THREAD_START));
    void* result = args->start_routine(args->arg);
    profiler::submit(std::make_unique<ThreadEvent>(EventType::THREAD_END));
    delete args;
    return result;
  };

  ThreadArgs* data = new ThreadArgs{start_routine, arg};
  return real_pthread_create(thread, attr, wrapper, data);
}

int pthread_join(pthread_t thread, void** value_ptr)
{
  if (!real_pthread_join) real_pthread_join = (int (*)(pthread_t, void**))dlsym(RTLD_NEXT, "pthread_join");

  if (profiling_disabled) return real_pthread_join(thread, value_ptr);

  int res = real_pthread_join(thread, value_ptr);

  // only emit after join is really done
  profiler::submit(std::make_unique<ThreadEvent>(EventType::THREAD_JOIN));
  return res;
}
