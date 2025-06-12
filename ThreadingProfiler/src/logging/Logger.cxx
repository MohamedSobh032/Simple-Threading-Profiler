#include "../../include/logging/Logger.hxx"

Logger *Logger::instance_{nullptr};
std::mutex Logger::mutex_;

Logger *Logger::get_instance()
{
    std::lock_guard<std::mutex> lock(mutex_);
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
