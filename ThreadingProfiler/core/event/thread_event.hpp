#ifndef _THREAD_EVENT
#define _THREAD_EVENT

#include <unistd.h>

#include "event.hpp"

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
