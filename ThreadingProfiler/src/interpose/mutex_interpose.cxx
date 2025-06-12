#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <dlfcn.h>
#include <stdio.h>
#include <time.h>

static int (*real_pthread_mutex_lock)(pthread_mutex_t *) = NULL;
static int (*real_pthread_mutex_trylock)(pthread_mutex_t *) = NULL;
static int (*real_pthread_mutex_unlock)(pthread_mutex_t *) = NULL;
static int (*real_pthread_mutex_init)(pthread_mutex_t *, const pthread_mutexattr_t *) = NULL;
static int (*real_pthread_mutex_destroy)(pthread_mutex_t *) = NULL;

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    if (!real_pthread_mutex_lock)
        real_pthread_mutex_lock = (int (*)(pthread_mutex_t *))dlsym(RTLD_NEXT, "pthread_mutex_lock");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Mutex is being locked at time %ld\n", time(NULL));

    return real_pthread_mutex_lock(mutex);
}

int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
    if (!real_pthread_mutex_trylock)
        real_pthread_mutex_trylock = (int (*)(pthread_mutex_t *))dlsym(RTLD_NEXT, "pthread_mutex_trylock");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Mutex is being trylocked at time %ld\n", time(NULL));

    return real_pthread_mutex_trylock(mutex);
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    if (!real_pthread_mutex_unlock)
        real_pthread_mutex_unlock = (int (*)(pthread_mutex_t *))dlsym(RTLD_NEXT, "pthread_mutex_unlock");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Mutex is being unlocked at time %ld\n", time(NULL));

    return real_pthread_mutex_unlock(mutex);
}

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    if (!real_pthread_mutex_init)
        real_pthread_mutex_init = (int (*)(pthread_mutex_t *, const pthread_mutexattr_t *))dlsym(RTLD_NEXT, "pthread_mutex_init");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Mutex is being initialized at time %ld\n", time(NULL));

    return real_pthread_mutex_init(mutex, attr);
}

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    if (!real_pthread_mutex_destroy)
        real_pthread_mutex_destroy = (int (*)(pthread_mutex_t *))dlsym(RTLD_NEXT, "pthread_mutex_destroy");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Mutex is being destroyed at time %ld\n", time(NULL));

    return real_pthread_mutex_destroy(mutex);
}
