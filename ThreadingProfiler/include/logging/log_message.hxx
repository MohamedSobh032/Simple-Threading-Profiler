#ifndef _LOG_MESSAGE
#define _LOG_MESSAGE

#include "log_types.hxx"
#include "log_entities.hxx"

#include <chrono>
#include <variant>

struct LogMessage
{
    LogType type;
    LogSeverity severity;
    std::chrono::time_point<std::chrono::system_clock> time;
    std::variant<ThreadInfo, MutexInfo, DeadlockInfo> data;
};

#endif