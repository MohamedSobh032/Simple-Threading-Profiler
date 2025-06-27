#include "profiler.hpp"

#include "../event/event_queue.hpp"
#include "global_tracker.hpp"

thread_local EventQueue lq;

void
profiler::submit(std::unique_ptr<Event> ev)
{
  // submit to local entry
  lq.push(std::move(ev));

  // submit to global tracker
  GlobalTracker::instance().record(*ev);
}
