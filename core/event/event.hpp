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

  Event(EventType type, uint64_t timestamp) : type_(type), timestamp_(timestamp)
  {
  }

 public:
  virtual ~Event() = default;
  virtual nlohmann::json to_json() const = 0;

  uint64_t get_timestamp() const noexcept
  {
    return this->timestamp_;
  }

  EventType get_event_type() const
  {
    return this->type_;
  }
};

#endif
