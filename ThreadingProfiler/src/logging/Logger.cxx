#include "Logger.hxx"

void Logger::add_logger(std::unique_pointer<Ilogger> logger)
{
    this->loggers.push_back(logger);
}

void Logger::log(const LogMessage &data)
{
    for (const auto &logger : this->loggers)
    {
        logger.log(data);
    }
}
