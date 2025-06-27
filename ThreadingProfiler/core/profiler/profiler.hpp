#ifndef _PROFILER
#define _PROFILER

#include "../event/event.hpp"

namespace profiler
{

void
submit(std::unique_ptr<Event> ev);

};  // namespace profiler

#endif
