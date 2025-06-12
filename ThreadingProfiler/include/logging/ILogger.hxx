#ifndef _ILOGGER
#define _ILOGGER

class ILogger
{
public:
    virtual void log(const LogMessage &data) = 0;
}

#endif