#include "logger.hpp"

#include "../concurrency/mpsc_queue.hpp"

Logger&
Logger::instance()
{
  static Logger logger_;
  return logger_;
}

void
Logger::add_logger(std::unique_ptr<ILogger> logger)
{
  this->loggers_.push_back(std::move(logger));
}

void
Logger::log(const Event& ev)
{
  for (const auto& logger : this->loggers_) logger->log(ev);
}

void
Logger::destruct()
{
  auto& q = MPSCQueue::instance();
  while (!q.empty())
  {
    auto e = q.pop();
    Logger::instance().log(*e);
  }
}
