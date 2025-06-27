#ifndef _LOGGER_INTERFACE
#define _LOGGER_INTERFACE

#include "../event/event.hpp"

template <typename T>
class ILogger
{
 public:
  virtual ~ILogger()            = default;
  virtual void log(const T& ev) = 0;
};

#endif
