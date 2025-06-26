#ifndef _EVENT_TYPES
#define _EVENT_TYPES

enum class EventType
{
  THRD_CRET,
  THRD_STRT,
  THRD_STOP,
  THRD_JOIN,

  MUTX_LOCK,
  MUTX_UNLK
};

#endif
