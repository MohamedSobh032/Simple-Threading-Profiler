#ifndef _EVENT_TYPES
#define _EVENT_TYPES

enum class EventType
{
  THREAD_CREATE,
  THREAD_START,
  THREAD_END,
  THREAD_JOIN,
  MUTEX_WAIT,
  MUTEX_LOCK,
  MUTEX_UNLOCK,
  DEAD_LOCK,
};

inline std::string to_string(EventType type)
{
  switch (type)
  {
    case EventType::THREAD_CREATE:
      return "THREAD_CREATE";
    case EventType::THREAD_START:
      return "THREAD_START";
    case EventType::THREAD_END:
      return "THREAD_END";
    case EventType::THREAD_JOIN:
      return "THREAD_JOIN";
    case EventType::MUTEX_WAIT:
      return "MUTEX_WAIT";
    case EventType::MUTEX_LOCK:
      return "MUTEX_LOCK";
    case EventType::MUTEX_UNLOCK:
      return "MUTEX_UNLK";
    case EventType::DEAD_LOCK:
      return "DEAD_LOCK";
    default:
      return "UNKNOWN";
  }
}

#endif
