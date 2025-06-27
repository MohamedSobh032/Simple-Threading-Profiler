#include "profiler.hpp"

void
profiler::submit(const Event& ev)
{
  // submit to local entry
  local_ev_q.push(e);
  // submit to global tracker
  // TODO: submit to global tracker
}
