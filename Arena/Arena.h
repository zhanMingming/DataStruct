#ifndef ZHANMM_ARENA_H_
#define ZHANMM_ARENA_H_

#include <atomic>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace zhanmm {

class Arena {
 public:
  Arena();

  Arena(const Arena&) = delete;
  Arena& operator=(const Arena&) = delete;

  ~Arena();

  // Return a pointer to a newly allocated memory block of "bytes" bytes.
  char* Allocate(size_t bytes);

  // Allocate memory with the normal alignment guarantees provided by malloc.
  char* AllocateAligned(size_t bytes);

  // Returns an estimate of the total memory usage of data allocated
  // by the arena.
  size_t MemoryUsage() const {
    return memory_usage_.load(std::memory_order_relaxed);
  }

 private:
  char* AllocateFallback(size_t bytes);
  char* AllocateNewBlock(size_t block_bytes);


  // 预先分配的内存块 头指针
  char* alloc_ptr_;
  // 剩余的内存块大小
  size_t alloc_bytes_remaining_;

  // Array of new[] allocated memory blocks
  // 所有分配的内存块的头指针数组
  std::vector<char*> blocks_;

  // Total memory usage of the arena.
  //
  // TODO(costan): This member is accessed via atomics, but the others are
  //               accessed without any locking. Is this OK?
  // 所有已申请内存块的大小之和
  std::atomic<size_t> memory_usage_;
};

}  // namespace zhanmm

#endif  // ZHANMM_ARENA_H_