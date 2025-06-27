#ifndef _EVENT_QUEUE
#define _EVENT_QUEUE

#include <queue>

#include "event.hpp"

class EventQueue
{
 private:
  std::queue<Event> q_;

  void flush();

 public:
  EventQueue();
  void push(const Event& ev);
  ~EventQueue();
};

#endif
