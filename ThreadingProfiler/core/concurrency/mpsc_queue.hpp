#ifndef _MPSC_QUEUE
#define _MPSC_QUEUE

#include <array>
#include <atomic>
#include <memory>

#include "../event/event.hpp"

const int SIZE = 1024;

class MPSCQueue
{
 private:
  std::array<std::unique_ptr<Event>, SIZE> buffer_;
  alignas(64) std::atomic<std::size_t> rear_;
  alignas(64) std::size_t front_;

  MPSCQueue() : rear_(0), front_(0)
  {
    for (auto& e : this->buffer_)
    {
      e = nullptr;
    }
  }

 public:
  MPSCQueue(MPSCQueue& other)           = delete;
  void operator=(const MPSCQueue other) = delete;

  static MPSCQueue& instance()
  {
    static MPSCQueue instance_;
    return instance_;
  }

  bool empty() const { return this->front_ == this->rear_.load(std::memory_order_acquire); }

  bool push(std::unique_ptr<Event> item)
  {
    std::size_t curr_rear = this->rear_.fetch_add(1, std::memory_order_acq_rel);
    std::size_t index     = curr_rear % SIZE;

    if (curr_rear - this->front_ >= SIZE)
    {
      return false;
    }

    this->buffer_[index] = std::move(item);
    return true;
  }

  std::unique_ptr<Event> pop()
  {
    if (this->empty()) return nullptr;
    std::size_t index    = this->front_ % SIZE;
    auto item            = std::move(this->buffer_[index]);
    this->buffer_[index] = nullptr;
    ++this->front_;
    return item;
  }
};

#endif
