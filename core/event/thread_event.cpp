#include "thread_event.hpp"

#include <sys/syscall.h>

#include "../utils/utils.hpp"

ThreadEvent::ThreadEvent(EventType t) : Event(t, utils::now())
{
  this->tid_ = syscall(SYS_gettid);
}

nlohmann::json ThreadEvent::to_json() const
{
  return nlohmann::json{{"tid", this->tid_}, {"timestamp", this->timestamp_}, {"type", to_string(this->type_)}};
}

pid_t ThreadEvent::get_thread_id() const noexcept
{
  return this->tid_;
}

ThreadEvent::~ThreadEvent()
{
  // nothing
}
