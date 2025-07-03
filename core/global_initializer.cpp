#include <stdio.h>

#include <thread>

#include "./logger/logger.hpp"
#include "./logger/tcp_logger.hpp"
#include "config.hpp"
#include "profiler_tls.hpp"

__attribute__((constructor)) static void global_initializer()
{
  Logger::instance().add_logger(std::make_unique<TCPLogger>(TCP_PORT));
  std::thread(
      []
      {
        profiling_disabled = true;
        while (true)
        {
          Logger::instance().flush_mpsc();
          std::this_thread::sleep_for(std::chrono::milliseconds(MPSC_FLUSH_TIMEOUT));
        }
      })
      .detach();
}

__attribute__((destructor)) static void global_destructor() { Logger::instance().flush_mpsc(); }