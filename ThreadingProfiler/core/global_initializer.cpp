#include <stdio.h>

#include "./logger/logger.hpp"
#include "./logger/tcp_logger.hpp"

__attribute__((constructor)) static void
global_initializer()
{
  Logger::instance().add_logger(std::make_unique<TCPLogger>(9090));
}

__attribute__((destructor)) static void
global_destructor()
{
  fprintf(stderr, "Destruct\n");
  Logger::instance().destruct();
}