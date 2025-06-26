#ifndef _THREAD_EVENT
#define _THREAD_EVENT

#include "event.hpp"
#include <unistd.h>

class ThreadEvent : public Event
{
private:
  pid_t tid_;

public:
  ThreadEvent(EventType t);
  ~ThreadEvent();

  pid_t get_thread_id() const noexcept;
};

#endif
