#ifndef _MUTEX_EVENT
#define _MUTEX_EVENT

#include <pthread.h>
#include <unistd.h>

#include "event.hpp"

class MutexEvent : public Event
{
 private:
  pid_t tid_;
  pthread_mutex_t* mid_;

 public:
  MutexEvent(EventType t, pthread_mutex_t* mid);
  ~MutexEvent();
  nlohmann::json to_json() const override;
  pid_t get_thread_id() const noexcept;
  pthread_mutex_t* get_mutex_id() const noexcept;
};

#endif
