#ifndef _LOG_ENTITIES
#define _LOG_ENTITIES
// TODO: ALL HERE IS TODO
#include <pthread.h>

struct ThreadInfo
{
    pthread_t id;
};

struct MutexInfo
{
    pthread_mutex_t *ptr;
    pthread_t thread_id;
};

struct DeadlockInfo
{
    int lolo;
};

#endif