#ifndef _EVENT
#define _EVENT

#include <cstdint>
#include <nlohmann/json.hpp>

#include "event_types.hpp"

class Event
{
 protected:
  EventType type_;
  uint64_t timestamp_;

 public:
  virtual ~Event()                       = default;
  virtual nlohmann::json to_json() const = 0;

  uint64_t get_timestamp() const noexcept { return this->timestamp_; }

  EventType get_event_type() { return this->type_; }
};

#endif
