#ifndef _EVENT_QUEUE
#define _EVENT_QUEUE

#include <memory>
#include <queue>

#include "event.hpp"

class EventQueue
{
 private:
  std::queue<std::unique_ptr<Event>> q_;
  void flush();

 public:
  EventQueue();
  void push(std::unique_ptr<Event> ev, bool force_flush);
  ~EventQueue();
};

#endif
