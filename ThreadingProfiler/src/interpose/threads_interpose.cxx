#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "../../include/logging/Logger.hxx"

#include <atomic>
#include <cstring>
#include <pthread.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static std::atomic<uint64_t> thread_counter{1};

ThreadInfo get_current_thread_info(uint64_t blocking_resource = 0)
{
    ThreadInfo info;

    // Custom logical TID (you may override if needed)
    info.tid = thread_counter;
    thread_counter++;

    // System thread ID
    info.system_tid = pthread_self();

    // Blocking resource (0 = not blocked)
    info.blocking_resource = blocking_resource;

    return info;
}

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
        .data = get_current_thread_info()};
    Logger::get_instance()->log(msg);

    struct ThreadArgs
    {
        void *(*start_routine)(void *);
        void *arg;
    };

    auto wrapper = [](void *data) -> void *
    {
        ThreadArgs *args = static_cast<ThreadArgs *>(data);

        LogMessage msg{
            .type = LogType::THREAD_START,
            .severity = LogSeverity::INFO,
            .time = std::chrono::system_clock::now(),
            .data = get_current_thread_info()};
        Logger::get_instance()->log(msg);

        void *result = args->start_routine(args->arg);

        msg.type = LogType::THREAD_FINISH;
        msg.time = std::chrono::system_clock::now();
        Logger::get_instance()->log(msg);

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

    LogMessage msg{
        .type = LogType::THREAD_JOIN,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = get_current_thread_info()};
    Logger::get_instance()->log(msg);

    return real_pthread_join(t, res);
}

void pthread_exit(void *value_ptr)
{
    if (!real_pthread_exit)
        real_pthread_exit = (void (*)(void *))dlsym(RTLD_NEXT, "pthread_exit");

    LogMessage msg{
        .type = LogType::THREAD_EXIT,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = get_current_thread_info()};
    Logger::get_instance()->log(msg);

    real_pthread_exit(value_ptr);
}

int pthread_cancel(pthread_t thread)
{
    if (!real_pthread_cancel)
        real_pthread_cancel = (int (*)(pthread_t))dlsym(RTLD_NEXT, "pthread_cancel");

    LogMessage msg{
        .type = LogType::THREAD_CANCEL,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = get_current_thread_info()};
    Logger::get_instance()->log(msg);

    return real_pthread_cancel(thread);
}
