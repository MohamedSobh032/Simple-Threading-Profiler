#ifndef _LOGGER_INTERFACE
#define _LOGGER_INTERFACE

#include "../event/event.hpp"

class ILogger
{
 public:
  virtual ~ILogger() = default;
  virtual void log(const Event& ev) = 0;
};

#endif
