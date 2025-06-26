#ifndef _TIME_STAMP
#define _TIME_STAMP

#include <chrono>

namespace utils
{

inline uint64_t
now()
{
  return std::chrono::steady_clock::now().time_since_epoch().count();
}

} // namespace utils

#endif
