#include "profiler.hpp"

#include "../event/deadlock_event.hpp"
#include "../event/event_queue.hpp"
#include "./mpsc_queue.hpp"
#include "global_tracker.hpp"

thread_local EventQueue lq;

void profiler::submit(std::unique_ptr<Event> ev)
{
  if (GlobalTracker::instance().record(ev.get()))
  {
    MPSCQueue::instance().push(std::make_unique<DeadlockEvent>(EventType::DEAD_LOCK));
    exit(EXIT_FAILURE);
  }
  lq.push(std::move(ev));
}
