#include "event_queue.hpp"

#define FLUSH_RATE 1

EventQueue::EventQueue()
{
  // nothing
}

void
EventQueue::push(const Event& ev)
{
  this->q_.push(ev);
  if (this->q_.size() == FLUSH_RATE)
  {
    this->flush();
  }
}

void
EventQueue::flush()
{
  // TODO: implement logic
}

EventQueue::~EventQueue() { this->flush(); }
