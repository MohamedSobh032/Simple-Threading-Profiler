#ifndef _LOGGER
#define _LOGGER

#include "ILogger.hxx"
#include <vector>
#include <memory>
#include <mutex>

class Logger
{
private:
    static Logger *instance_;
    static std::atomic<bool> ready_;
    std::vector<std::unique_ptr<ILogger>> loggers;

    Logger() = default;

public:
    Logger(Logger &other) = delete;
    void operator=(const Logger other) = delete;

    static Logger *get_instance();
    void add_logger(std::unique_ptr<ILogger> logger);
    void log(const LogMessage &data);
};

#endif