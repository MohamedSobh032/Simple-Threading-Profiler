#include "profiler.hpp"

#include "global_tracker.hpp"

thread_local EventQueue local_ev_q;

void
profiler::submit(const Event& ev)
{
  // submit to local entry
  local_ev_q.push(ev);
  // submit to global tracker
  GlobalTracker::instance().record(ev);
}
