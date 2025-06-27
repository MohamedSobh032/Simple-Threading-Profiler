#include "event_queue.hpp"

#include "../concurrency/mpsc_queue.hpp"

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
  auto& ins_ = MPSCQueue::instance();
  while (!this->q_.empty())
  {
    Event e = std::move(this->q_.front());
    this->q_.pop();

    auto ptr = std::make_unique<Event>(std::move(e));
    ins_.push(std::move(ptr));
  }
}

EventQueue::~EventQueue() { this->flush(); }
