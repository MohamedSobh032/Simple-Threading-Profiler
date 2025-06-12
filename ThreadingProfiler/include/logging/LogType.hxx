#ifndef _LOG_TYPE
#define _LOG_TYPE

#include <string>
#include <chrono>

enum class LogSeverity
{
    INFO,
    ERROR
};

enum class LogType
{
    // thread logs
    THREAD_CREATE,
    THREAD_JOIN,
    THREAD_EXIT,
    THREAD_CANCEL,
    // mutex logs
    MUTEX_CREATE,
    MUTEX_DESTROYED,
    MUTEX_LOCK,
    MUTEX_UNLOCK,
    // errors
    DEADLOCK_DETECT,
};

struct LogMessage
{
    LogType type;
    LogSeverity severity;
    const std::string message;
    std::chrono::timestamp time;
};

#endif