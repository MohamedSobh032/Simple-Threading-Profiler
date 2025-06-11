#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static int (*real_pthread_create)(pthread_t *, const pthread_attr_t *attr, void *(*start_routine)(void *), void *) = NULL;

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
    if (!real_pthread_create)
        real_pthread_create = (int (*)(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *))dlsym(RTLD_NEXT, "pthread_create");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Thread is being created at time %ld\n", time(NULL));

    struct ThreadArgs
    {
        void *(*start_routine)(void *);
        void *arg;
    };

    auto wrapper = [](void *data) -> void *
    {
        ThreadArgs *args = static_cast<ThreadArgs *>(data);
        fprintf(stderr, "[Profiler] Thread started\n");
        void *result = args->start_routine(args->arg);
        fprintf(stderr, "[Profiler] Thread exited\n");
        delete args;
        return result;
    };

    ThreadArgs *data = new ThreadArgs{start_routine, arg};
    return real_pthread_create(thread, attr, wrapper, data);
}
