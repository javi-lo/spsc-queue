#ifndef SPSC_QUEUE_H_
#define SPSC_QUEUE_H_

#include <atomic>
#include <cstddef>
#include <memory>
#include <new>

namespace javilo
{

template<typename T, typename Alloc = std::allocator<T>>
class spsc_queue
{
  using allocator_traits = std::allocator_traits<Alloc>;
  using allocator_type = allocator_traits::allocator_type;
  using size_type = typename allocator_traits::size_type;

public:
  explicit spsc_queue(size_type capacity, const Alloc& allocator = Alloc{})
    : allocator_{allocator}
    , capacity_{capacity}
    , data_{allocator_traits::allocate(allocator_, capacity)}
  { }

  ~spsc_queue()
  {
    allocator_traits::deallocate(allocator_, data_, capacity_);
  }

  spsc_queue(const spsc_queue&) = delete;
  spsc_queue& operator=(const spsc_queue&) = delete;

  bool push(const T& item)
  {
    (void)item;

    return true;
  }

  bool pop(T& item)
  {
    (void)item;

    return true;
  }

private:
  allocator_type allocator_;

  size_type capacity_;

  T* data_;

  // align to prevent false sharing
  alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> push_;

  // align to prevent false sharing
  alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> pop_;

  char padding_[std::hardware_destructive_interference_size - sizeof(size_type)];
};

}

#endif
