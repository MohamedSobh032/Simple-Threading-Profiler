#ifndef _GNU_SOURCE
#    define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>

static int (*real_pthread_create)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*) = NULL;
static int (*real_pthread_join)(pthread_t, void**) = NULL;

int
pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg)
{
    if (!real_pthread_create)
        real_pthread_create =
            (int (*)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*))dlsym(RTLD_NEXT, "pthread_create");

    fprintf(stderr, "[PROFILER] pthread_create called\n");

    int result = real_pthread_create(thread, attr, start_routine, arg);

    fprintf(stderr, "[PROFILER] pthread_create returned %d\n", result);

    return result;
}

int
pthread_join(pthread_t thread, void** value_ptr)
{
    if (!real_pthread_join)
        real_pthread_join = (int (*)(pthread_t, void**))dlsym(RTLD_NEXT, "pthread_join");

    fprintf(stderr, "[PROFILER] pthread_join called\n");

    int result = real_pthread_join(thread, value_ptr);

    fprintf(stderr, "[PROFILER] pthread_join returned %d\n", result);

    return result;
}