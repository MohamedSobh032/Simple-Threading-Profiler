#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

static int (*real_pthread_create)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*) = NULL;
static int (*real_pthread_join)(pthread_t, void**)                                            = NULL;

struct ThreadArgs
{
  void* (*start_routine)(void*);
  void* arg;
};

int
pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg)
{
  if (!real_pthread_create)
    real_pthread_create =
        (int (*)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*))dlsym(RTLD_NEXT, "pthread_create");

  // TODO: REMOVE
  fprintf(stderr, "[PROFILER] pthread_create called\n");

  auto wrapper = [](void* data)
  {
    ThreadArgs* args = static_cast<ThreadArgs*>(data);

    // TODO: REMOVE
    fprintf(stderr, "[PROFILER] thread started\n");

    void* result = args->start_routine(args->arg);

    // TODO: REMOVE
    fprintf(stderr, "[PROFILER] thread ended\n");

    delete args;
    return result;
  };

  ThreadArgs* data = new ThreadArgs{start_routine, arg};
  int result       = real_pthread_create(thread, attr, wrapper, data);

  pid_t tid        = syscall(SYS_gettid);

  // TODO: REMOVE
  fprintf(stderr, "[PROFILER] pthread_create returned %d using id: %d\n", result, static_cast<int>(tid));

  return result;
}

int
pthread_join(pthread_t thread, void** value_ptr)
{
  if (!real_pthread_join) real_pthread_join = (int (*)(pthread_t, void**))dlsym(RTLD_NEXT, "pthread_join");

  fprintf(stderr, "[PROFILER] pthread_join called\n");

  int result = real_pthread_join(thread, value_ptr);

  fprintf(stderr, "[PROFILER] pthread_join returned %d\n", result);

  return result;
}
