#ifndef _MPSC_QUEUE
#define _MPSC_QUEUE

#include <array>
#include <atomic>
#include <memory>

#include "../config.hpp"
#include "../event/event.hpp"

class MPSCQueue
{
 private:
  std::array<std::unique_ptr<Event>, QUEUE_BUFFER_SIZE> buffer_;
  alignas(64) std::atomic<std::size_t> rear_;
  alignas(64) std::size_t front_;

  MPSCQueue();

 public:
  MPSCQueue(MPSCQueue& other) = delete;
  void operator=(const MPSCQueue other) = delete;

  static MPSCQueue& instance();
  bool empty() const;
  bool push(std::unique_ptr<Event> item);
  std::unique_ptr<Event> pop();
};

#endif
