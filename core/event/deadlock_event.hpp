#ifndef _DEADLOCK_EVENT
#define _DEADLOCK_EVENT

#include "event.hpp"

class DeadlockEvent : public Event
{
 public:
  DeadlockEvent(EventType t);
  ~DeadlockEvent();
  nlohmann::json to_json() const override;
};

#endif
