#include "global_tracker.hpp"

#include "../event/mutex_event.hpp"

bool
GlobalTracker::detect_cycle(const pid_t tid, pthread_mutex_t* mid)
{
  void* tid_ptr = reinterpret_cast<void*>(tid);
  void* mid_ptr = reinterpret_cast<void*>(mid);
  this->adj_[tid_ptr].push_back(mid_ptr);

  std::unordered_map<void*, bool> visited;
  std::unordered_map<void*, bool> rec_stack;
  for (const auto& pair : this->adj_)
  {
    if (this->dfs(pair.first, visited, rec_stack))
    {
      return true;
    }
  }
  return false;
}

bool
GlobalTracker::dfs(void* node, std::unordered_map<void*, bool>& visited, std::unordered_map<void*, bool>& rec_stack)
{
  if (!visited[node])
  {
    visited[node]   = true;
    rec_stack[node] = true;

    for (auto& neighbor : this->adj_[node])
    {
      if (!visited[neighbor] && dfs(neighbor, visited, rec_stack))
        return true;
      else if (rec_stack[neighbor])
        return true;
    }
  }
  rec_stack[node] = false;
  return false;
}

void
GlobalTracker::remove_edge(void* from, void* to)
{
  auto& vec = adj_[from];
  vec.erase(std::remove(vec.begin(), vec.end(), to), vec.end());
}

GlobalTracker&
GlobalTracker::instance()
{
  static GlobalTracker instance_;
  return instance_;
}

bool
GlobalTracker::record(const Event* ev)
{
  if (!ev)
    fprintf(stderr, "ev is nullptr!\n");
  else
    fprintf(stderr, "ev type: %s\n", typeid(*ev).name());

  if (auto mutex_ev = dynamic_cast<const MutexEvent*>(ev))
  {
    EventType type       = mutex_ev->get_event_type();
    pthread_mutex_t* mid = mutex_ev->get_mutex_id();
    pid_t tid            = mutex_ev->get_thread_id();
    switch (type)
    {
      case EventType::MUTEX_WAIT:
        fprintf(stderr, "Cycle detection started\n");
        return this->detect_cycle(tid, mid);
      case EventType::MUTEX_LOCK:
        this->remove_edge(reinterpret_cast<void*>(tid), reinterpret_cast<void*>(mid));
        this->adj_[reinterpret_cast<void*>(mid)].push_back(reinterpret_cast<void*>(tid));
        break;
      case EventType::MUTEX_UNLOCK:
        this->remove_edge(reinterpret_cast<void*>(mid), reinterpret_cast<void*>(tid));
        break;
    }
  }
  return false;
}
