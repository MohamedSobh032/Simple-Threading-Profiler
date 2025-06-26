#ifndef _EVENT_QUEUE
#define _EVENT_QUEUE

#include "event.hpp"
#include <queue>

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
