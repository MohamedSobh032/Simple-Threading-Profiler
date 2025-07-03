#ifndef _UTILS
#define _UTILS

#include <chrono>

namespace utils
{

inline uint64_t now() { return std::chrono::steady_clock::now().time_since_epoch().count(); }

}  // namespace utils

#endif
