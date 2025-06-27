#ifndef _EVENT
#define _EVENT

#include <cstdint>

#include "event_types.hpp"

class Event
{
 protected:
  EventType type_;
  uint64_t timestamp_;

 public:
  virtual ~Event() = default;

  uint64_t get_timestamp() const noexcept { return this->timestamp_; }

  EventType get_event_type() { return this->type_; }
};

#endif
