#include "thread_event.hpp"
#include "../utils/timestamp.hpp"
#include <sys/syscall.h>

ThreadEvent::ThreadEvent(EventType t)
{
  this->type_ = t;
  this->timestamp_ = utils::now();
  this->tid_ = syscall(SYS_gettid);
}

pid_t
ThreadEvent::get_thread_id() const noexcept
{
  return this->tid_;
}

ThreadEvent::~ThreadEvent()
{
  // nothing
}