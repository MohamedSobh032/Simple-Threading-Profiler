#include "../../include/logging/Logger.hxx"

#include <atomic>

Logger *Logger::instance_{nullptr};
std::atomic<bool> Logger::ready_{false};

Logger *Logger::get_instance()
{
    if (instance_ == nullptr)
        instance_ = new Logger();
    return instance_;
}

void Logger::add_logger(std::unique_ptr<ILogger> logger)
{
    this->loggers.push_back(std::move(logger));
}

void Logger::log(const LogMessage &data)
{
    for (const auto &logger : this->loggers)
        logger->log(data);
}
