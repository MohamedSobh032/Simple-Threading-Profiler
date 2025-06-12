#ifndef _LOGGER
#define _LOGGER

#include "LogType.hxx"

class Logger
{
private:
    static Logger instance;
    std::vector<std::unique_pointer<ILogger>> loggers;

public:
    static Logger &get_instance();
    void add_logger(std::unique_pointer<Ilogger> logger);
    void log(const LogMessage &data);
}

#endif