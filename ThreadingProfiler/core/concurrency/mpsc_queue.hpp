#ifndef _MPSC_QUEUE
#define _MPSC_QUEUE

#include <array>
#include <atomic>

template <typename T, std::size_t SIZE>
class MPSCQueue
{
  static_assert((SIZE & (SIZE - 1)) == 0, "SIZE must be power of two for efficient modulo");

 private:
  std::array<T*, SIZE> buffer_;
  alignas(64) std::atomic<std::size_t> rear_;
  alignas(64) std::size_t front_;

 public:
  MPSCQueue() : rear_(0), front_(0) { this->buffer_.fill(nullptr); }

  bool empty() const { return this->front_ == this->rear_.load(std::memory_order_acquire); }

  bool push(const T* item)
  {
    std::size_t curr_rear = this->rear_.fetch_add(1, std::memory_order_acq_rel);
    std::size_t index     = curr_rear % SIZE;

    if (curr_rear - this->front_ >= SIZE)
    {
      return false;
    }

    this->buffer_[index] = item;
    return true;
  }

  T* pop()
  {
    if (this->empty()) return nullptr;
    std::size_t index    = this->front_ % SIZE;
    T* item              = this->buffer_[index];
    this->buffer_[index] = nullptr;
    ++this->front_;
    return item;
  }

  ~MPSCQueue()
  {
    for (auto& ptr : this->buffer_)
    {
      delete ptr;
      ptr = nullptr;
    }
  }
};

#endif
