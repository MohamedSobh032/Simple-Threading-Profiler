#include "event_queue.hpp"

#include "../config.hpp"
#include "../profiler/mpsc_queue.hpp"

EventQueue::EventQueue()
{
  // nothing
}

void EventQueue::push(std::unique_ptr<Event> ev)
{
  this->q_.push(std::move(ev));
  if (this->q_.size() == LOCAL_QUEUE_FLUSH_RATE)
  {
    this->flush();
  }
}

void EventQueue::flush()
{
  auto& ins_ = MPSCQueue::instance();
  while (!this->q_.empty())
  {
    ins_.push(std::move(this->q_.front()));
    this->q_.pop();
  }
}

EventQueue::~EventQueue() { this->flush(); }
