#ifndef _TCP_LOGGER
#define _TCP_LOGGER

#include "ILogger.hxx"
#include <netinet/in.h>

class TCPLogger : public ILogger
{
private:
    int server_fd, client_fd;
    sockaddr_in address{};
    bool connected = false;

public:
    TCPLogger(int port = 9090);
    void log(const LogMessage &data);
    ~TCPLogger();
};

#endif