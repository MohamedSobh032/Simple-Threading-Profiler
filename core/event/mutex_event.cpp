#include "mutex_event.hpp"

#include <sys/syscall.h>

#include "../utils/utils.hpp"

MutexEvent::MutexEvent(EventType t, pthread_mutex_t* mid) : Event(t, utils::now())
{
  this->tid_ = syscall(SYS_gettid);
  this->mid_ = mid;
}

nlohmann::json MutexEvent::to_json() const
{
  return nlohmann::json{{"tid", this->tid_},
                        {"mutex", reinterpret_cast<uintptr_t>(this->mid_)},
                        {"timestamp", this->timestamp_},
                        {"type", to_string(this->type_)}};
}

pid_t MutexEvent::get_thread_id() const noexcept { return this->tid_; }

pthread_mutex_t* MutexEvent::get_mutex_id() const noexcept { return this->mid_; }

MutexEvent::~MutexEvent()
{
  // nothing
}