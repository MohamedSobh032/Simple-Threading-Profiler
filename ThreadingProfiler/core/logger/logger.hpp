#ifndef _LOGGER
#define _LOGGER

#include <memory>
#include <vector>

#include "logger_interface.hpp"

class Logger
{
 private:
  std::vector<std::unique_ptr<ILogger>> loggers_;
  Logger() = default;

 public:
  Logger(const Logger& other)        = delete;
  void operator=(const Logger other) = delete;

  static Logger& instance();
  void add_logger(std::unique_ptr<ILogger> logger);
  void log(const Event& ev);
  void flush_mpsc();
  void destruct();
};

#endif
