#include "mpsc_queue.hpp"

#include <cstdio>

MPSCQueue::MPSCQueue() : rear_(0), front_(0)
{
  for (auto& e : this->buffer_)
  {
    e = nullptr;
  }
}

MPSCQueue& MPSCQueue::instance()
{
  static MPSCQueue* instance_ = new MPSCQueue();
  return *instance_;
}

bool MPSCQueue::empty() const
{
  return this->front_ == this->rear_.load(std::memory_order_acquire);
}

bool MPSCQueue::push(std::unique_ptr<Event> item)
{
  while (true)
  {
    std::size_t curr_rear = this->rear_.load(std::memory_order_acquire);
    std::size_t curr_front = this->front_;

    if (curr_rear - curr_front >= QUEUE_BUFFER_SIZE)
    {
      return false;
    }

    std::size_t index = curr_rear % QUEUE_BUFFER_SIZE;

    if (this->buffer_[index] == nullptr)
    {
      this->buffer_[index] = std::move(item);
      this->rear_.fetch_add(1, std::memory_order_release);
      return true;
    }
  }
}

std::unique_ptr<Event> MPSCQueue::pop()
{
  if (this->empty()) return nullptr;

  std::size_t index = this->front_ % QUEUE_BUFFER_SIZE;
  auto item = std::move(this->buffer_[index]);
  this->buffer_[index] = nullptr;
  ++this->front_;
  return item;
}

void MPSCQueue::check_nulls()
{
  std::size_t curr_rear = this->rear_.load(std::memory_order_acquire);
  for (std::size_t i = this->front_; i < curr_rear; ++i)
  {
    std::size_t index = i % QUEUE_BUFFER_SIZE;
    if (!this->buffer_[index])
    {
      printf("[MPSCQueue] NULL at index %ld (absolute pos %ld)\n", index, i);
    }
  }
}
