#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "../../include/logging/Logger.hxx"

#include <pthread.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static int (*real_pthread_create)(pthread_t *, const pthread_attr_t *attr, void *(*start_routine)(void *), void *) = NULL;
static int (*real_pthread_join)(pthread_t, void **) = NULL;
static void (*real_pthread_exit)(void *) = NULL;
static int (*real_pthread_cancel)(pthread_t) = NULL;

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
    if (!real_pthread_create)
        real_pthread_create = (int (*)(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *))dlsym(RTLD_NEXT, "pthread_create");

    LogMessage msg{
        .type = LogType::THREAD_CREATE,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = ThreadInfo{pthread_self()}};
    Logger::get_instance()->log(msg);

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

int pthread_join(pthread_t t, void **res)
{
    if (!real_pthread_join)
        real_pthread_join = (int (*)(pthread_t, void **))dlsym(RTLD_NEXT, "pthread_join");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Thread is being joined at time %ld\n", time(NULL));

    return real_pthread_join(t, res);
}

void pthread_exit(void *value_ptr)
{
    if (!real_pthread_exit)
        real_pthread_exit = (void (*)(void *))dlsym(RTLD_NEXT, "pthread_exit");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Thread is being exited at time %ld\n", time(NULL));

    real_pthread_exit(value_ptr);
}

int pthread_cancel(pthread_t thread)
{
    if (!real_pthread_cancel)
        real_pthread_cancel = (int (*)(pthread_t))dlsym(RTLD_NEXT, "pthread_cancel");

    // Log thread creation timestamp, thread ID (after join), etc.
    fprintf(stderr, "[Profiler] Thread is being cancelled at time %ld\n", time(NULL));

    return real_pthread_cancel(thread);
}
