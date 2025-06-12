#ifndef _LOG_TYPES
#define _LOG_TYPES

enum class LogSeverity
{
    INFO,
    ERROR
};

inline const char *to_string(const LogSeverity &severity)
{
    switch (severity)
    {
    case LogSeverity::INFO:
        return "INFO";
    case LogSeverity::ERROR:
        return "ERROR";
    }
    return "UNKNOWN";
}

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

inline const char *to_string(LogType type)
{
    switch (type)
    {
    case LogType::THREAD_CREATE:
        return "THREAD_CREATE";
    case LogType::THREAD_JOIN:
        return "THREAD_JOIN";
    case LogType::THREAD_EXIT:
        return "THREAD_EXIT";
    case LogType::THREAD_CANCEL:
        return "THREAD_CANCEL";
    case LogType::MUTEX_CREATE:
        return "MUTEX_CREATE";
    case LogType::MUTEX_DESTROYED:
        return "MUTEX_DESTROYED";
    case LogType::MUTEX_LOCK:
        return "MUTEX_LOCK";
    case LogType::MUTEX_UNLOCK:
        return "MUTEX_UNLOCK";
    case LogType::DEADLOCK_DETECT:
        return "DEADLOCK_DETECT";
    }
    return "UNKNOWN";
}

#endif