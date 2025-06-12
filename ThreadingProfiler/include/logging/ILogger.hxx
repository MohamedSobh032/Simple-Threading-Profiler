#ifndef _ILOGGER
#define _ILOGGER

#include "log_message.hxx"
class ILogger
{
public:
    virtual void log(const LogMessage &data) = 0;
};

#endif