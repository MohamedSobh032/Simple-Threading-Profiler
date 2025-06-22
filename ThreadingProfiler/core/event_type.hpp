#ifndef _EVENT_TYPE
#define _EVENT_TYPE

enum class EventType
{
    THREAD_CREATE,
    THREAD_JOIN,
    MUTEX_LOCK,
    MUTEX_UNLOCK
};

#endif
