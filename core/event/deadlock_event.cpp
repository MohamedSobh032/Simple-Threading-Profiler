#include "deadlock_event.hpp"

#include "../utils/utils.hpp"

DeadlockEvent::DeadlockEvent(EventType t) : Event(t, utils::now()) {}

DeadlockEvent::~DeadlockEvent()
{
  // nothing
}

nlohmann::json DeadlockEvent::to_json() const
{
  return nlohmann::json{{"timestamp", this->timestamp_}, {"type", to_string(this->type_)}};
}
