#ifndef _GLOBAL_TRACKER
#define _GLOBAL_TRACKER

#include <unordered_map>
#include <vector>

#include "../event/event.hpp"

class GlobalTracker
{
 private:
  std::unordered_map<void*, std::vector<void*>> adj_;

  bool detect_cycle(const pid_t tid, pthread_mutex_t* mid);
  bool dfs(void* node, std::unordered_map<void*, bool>& visited, std::unordered_map<void*, bool>& rec_stack);
  void remove_edge(void* p1, void* p2);

  GlobalTracker() = default;

 public:
  // delete copy constructor and assignment operator
  GlobalTracker(GlobalTracker& other)       = delete;
  void operator=(const GlobalTracker other) = delete;

  static GlobalTracker& instance();
  bool record(const Event* ev);
};

#endif
