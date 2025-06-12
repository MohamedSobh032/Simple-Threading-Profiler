#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "../../include/logging/Logger.hxx"

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

    LogMessage msg{
        .type = LogType::MUTEX_LOCK,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = ThreadInfo{pthread_self()}};
    Logger::get_instance()->log(msg);

    return real_pthread_mutex_lock(mutex);
}

int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
    if (!real_pthread_mutex_trylock)
        real_pthread_mutex_trylock = (int (*)(pthread_mutex_t *))dlsym(RTLD_NEXT, "pthread_mutex_trylock");

    LogMessage msg{
        .type = LogType::MUTEX_TRYLOCK,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = ThreadInfo{pthread_self()}};
    Logger::get_instance()->log(msg);

    return real_pthread_mutex_trylock(mutex);
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    if (!real_pthread_mutex_unlock)
        real_pthread_mutex_unlock = (int (*)(pthread_mutex_t *))dlsym(RTLD_NEXT, "pthread_mutex_unlock");

    LogMessage msg{
        .type = LogType::MUTEX_UNLOCK,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = ThreadInfo{pthread_self()}};
    Logger::get_instance()->log(msg);

    return real_pthread_mutex_unlock(mutex);
}

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    if (!real_pthread_mutex_init)
        real_pthread_mutex_init = (int (*)(pthread_mutex_t *, const pthread_mutexattr_t *))dlsym(RTLD_NEXT, "pthread_mutex_init");

    LogMessage msg{
        .type = LogType::MUTEX_CREATE,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = ThreadInfo{pthread_self()}};
    Logger::get_instance()->log(msg);

    return real_pthread_mutex_init(mutex, attr);
}

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    if (!real_pthread_mutex_destroy)
        real_pthread_mutex_destroy = (int (*)(pthread_mutex_t *))dlsym(RTLD_NEXT, "pthread_mutex_destroy");

    LogMessage msg{
        .type = LogType::MUTEX_DESTROYED,
        .severity = LogSeverity::INFO,
        .time = std::chrono::system_clock::now(),
        .data = ThreadInfo{pthread_self()}};
    Logger::get_instance()->log(msg);

    return real_pthread_mutex_destroy(mutex);
}
