#include "deadlock_event.hpp"

#include "../utils/timestamp.hpp"

DeadlockEvent::DeadlockEvent(EventType t)
{
  this->type_      = t;
  this->timestamp_ = utils::now();
}

DeadlockEvent::~DeadlockEvent()
{
  // nothing
}

nlohmann::json
DeadlockEvent::to_json() const
{
  return nlohmann::json{{"timestamp", this->timestamp_}, {"type", to_string(this->type_)}};
}
