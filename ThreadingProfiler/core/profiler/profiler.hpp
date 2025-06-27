#ifndef _PROFILER
#define _PROFILER

#include "../event/event.hpp"
#include "../event/event_queue.hpp"

namespace profiler
{

void
submit(const Event& ev);

};  // namespace profiler

#endif
