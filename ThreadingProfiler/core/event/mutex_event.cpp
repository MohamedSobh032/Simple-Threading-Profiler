#include "mutex_event.hpp"
#include "../utils/timestamp.hpp"
#include <sys/syscall.h>

MutexEvent::MutexEvent(EventType t, pthread_mutex_t* mid)
{
  this->type_ = t;
  this->timestamp_ = utils::now();
  this->tid_ = syscall(SYS_gettid);
  this->mid_ = mid;
}

pid_t
MutexEvent::get_thread_id() const noexcept
{
  return this->tid_;
}

pthread_mutex_t*
MutexEvent::get_mutex_id() const noexcept
{
  return this->mid_;
}

MutexEvent::~MutexEvent()
{
  // nothing
}