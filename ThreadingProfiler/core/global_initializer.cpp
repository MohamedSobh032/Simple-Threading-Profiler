#include <stdio.h>

#include <thread>

#include "./logger/logger.hpp"
#include "./logger/tcp_logger.hpp"
#include "profiler_tls.hpp"

#define WAIT_FOR 100

__attribute__((constructor)) static void
global_initializer()
{
  Logger::instance().add_logger(std::make_unique<TCPLogger>(9090));
  // profiling_disabled = true;
  std::thread(
      []
      {
        profiling_disabled = true;  // tell your profiler not to instrument this thread
        while (true)
        {
          Logger::instance().flush_mpsc();
          std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR));
        }
      })
      .detach();
  // profiling_disabled = false;
}

__attribute__((destructor)) static void
global_destructor()
{
  Logger::instance().destruct();
}