#ifndef _PROFILER
#define _PROFILER

#include "../event/event.hpp"
#include "../event/event_queue.hpp"

namespace profiler
{

thread_local EventQueue local_ev_q;

void
submit(const Event& ev);

}; // namespace profiler

#endif
