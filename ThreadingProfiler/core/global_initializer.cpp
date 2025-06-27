#include "./concurrency/mpsc_queue.hpp"
#include <stdio.h>

__attribute__((constructor)) static void
global_initializer()
{
}

__attribute__((destructor)) static void
global_destructor()
{
  fprintf(stderr, "Destruct\n");
}