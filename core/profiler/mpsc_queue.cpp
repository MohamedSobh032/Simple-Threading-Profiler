#include "mpsc_queue.hpp"

MPSCQueue::MPSCQueue() : rear_(0), front_(0)
{
  for (auto& e : this->buffer_)
  {
    e = nullptr;
  }
}

MPSCQueue& MPSCQueue::instance()
{
  static MPSCQueue instance_;
  return instance_;
}

bool MPSCQueue::empty() const { return this->front_ == this->rear_.load(std::memory_order_acquire); }

bool MPSCQueue::push(std::unique_ptr<Event> item)
{
  std::size_t curr_rear = this->rear_.fetch_add(1, std::memory_order_acq_rel);
  std::size_t index = curr_rear % QUEUE_BUFFER_SIZE;

  if (curr_rear - this->front_ >= QUEUE_BUFFER_SIZE)
  {
    return false;
  }

  this->buffer_[index] = std::move(item);
  return true;
}

std::unique_ptr<Event> MPSCQueue::pop()
{
  if (this->empty()) return nullptr;
  std::size_t index = this->front_ % QUEUE_BUFFER_SIZE;
  auto item = std::move(this->buffer_[index]);
  this->buffer_[index] = nullptr;
  ++this->front_;
  return item;g
}