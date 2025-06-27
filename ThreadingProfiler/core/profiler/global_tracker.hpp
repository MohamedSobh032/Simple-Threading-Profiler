#ifndef _GLOBAL_TRACKER
#define _GLOBAL_TRACKER

#include <pthread.h>

#include <unordered_map>

#include "../event/event.hpp"

class GlobalTracker
{
 private:
  std::unordered_map<pthread_mutex_t*, pid_t> acquisition_;

  GlobalTracker() = default;

 public:
  // delete copy constructor and assignment operator
  GlobalTracker(GlobalTracker& other)       = delete;
  void operator=(const GlobalTracker other) = delete;

  static GlobalTracker& instance()
  {
    static GlobalTracker instance_;
    return instance_;
  }

  bool record(const Event& ev)
  {
    // TODO: implement deadlock detector logic
    return true;
  }
};

#endif
