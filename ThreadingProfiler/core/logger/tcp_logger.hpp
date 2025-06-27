#ifndef _TCP_LOGGER
#define _TCP_LOGGER

#include <netinet/in.h>

#include "logger_interface.hpp"

class TCPLogger : public ILogger
{
 private:
  int server_fd, client_fd;
  sockaddr_in address;
  bool connected = false;

 public:
  TCPLogger(int port = 9000);
  void log(const Event& ev);
  ~TCPLogger();
};

#endif
