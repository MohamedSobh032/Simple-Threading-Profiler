#ifndef _LOG_ENTITIES
#define _LOG_ENTITIES
#include <pthread.h>
#include <vector>
#include <string>
#include <stdint.h>

struct ThreadInfo
{
    uint64_t tid;               // Unique thread ID
    pthread_t system_tid;       // System thread identifier
    uint64_t blocking_resource; // Mutex/CV ID causing blocking (0 if none)
};

struct MutexInfo
{
    uint64_t mid;         // Unique mutex ID
    pthread_mutex_t *ptr; // System mutex pointer
    uint64_t owner_tid;   // Current owner thread ID (0 if unlocked)
};

struct DeadlockInfo
{
    std::vector<pthread_t> involved_threads;
    std::vector<pthread_mutex_t *> involved_mutexes;
    std::string message; // High-level summary: e.g., "Cycle detected: T1 → M1 → T2 → M2 → T1"
};

#endif