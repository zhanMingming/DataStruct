
#include "Arena.h"

namespace zhanmm {

static const int kBlockSize = 4096;

Arena::Arena()
    : alloc_ptr_(nullptr), alloc_bytes_remaining_(0), memory_usage_(0) {}

Arena::~Arena() {
  for (size_t i = 0; i < blocks_.size(); i++) {
    delete[] blocks_[i];
  }
}

char* Arena::Allocate(size_t bytes) {
  // The semantics of what to return are a bit messy if we allow
  // 0-byte allocations, so we disallow them here (we don't need
  // them for our internal use).
  assert(bytes > 0);
  // 如果申请的字节数 小于 剩余的内存块大小，则直接进行分配
  if (bytes <= alloc_bytes_remaining_) {
    char* result = alloc_ptr_;
    alloc_ptr_ += bytes;
    alloc_bytes_remaining_ -= bytes;
    return result;
  }
  // 否则需要向操作系统申请内存
  return AllocateFallback(bytes);
}


char* Arena::AllocateFallback(size_t bytes) {
  
  // 如果申请的内存大小 大于 1KB, 为了减少内存碎片，
  // 我们单独向操作系统申请分配内存
  if (bytes > kBlockSize / 4) {
    // Object is more than a quarter of our block size.  Allocate it separately
    // to avoid wasting too much space in leftover bytes.
    char* result = AllocateNewBlock(bytes);
    return result;
  }
  
  // 这里重新分配了空间，重置了头指针
  // 但浪费了已有的内存块空间，后面需要优化这块
  // We waste the remaining space in the current block.
  alloc_ptr_ = AllocateNewBlock(kBlockSize);
  alloc_bytes_remaining_ = kBlockSize;
  
  // 重置分配的头指针
  char* result = alloc_ptr_;
  alloc_ptr_ += bytes;
  alloc_bytes_remaining_ -= bytes;
  return result;
}

char* Arena::AllocateAligned(size_t bytes) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  
  static_assert((align & (align - 1)) == 0,
                "Pointer size should be a power of 2");
  
  // 将alloc_prt_ 地址作为数字 与 align-1 进行与运算
  size_t current_mod = reinterpret_cast<uintptr_t>(alloc_ptr_) & (align - 1);
  
  
  // 假如curent_mod = 33 & (8-1) = 1, 则 slop = 8 -1 = 7 
  size_t slop = (current_mod == 0 ? 0 : align - current_mod);
  
  // 为了内存对齐，需要多分配 slop 个字节
  size_t needed = bytes + slop;
  char* result;
  // 如果所需分配内存大小 小于 已有内存大小 则直接分配
  if (needed <= alloc_bytes_remaining_) {
    result = alloc_ptr_ + slop;
    alloc_ptr_ += needed;
    alloc_bytes_remaining_ -= needed;
  } else {
    // 否则申请分配新的内存
    // AllocateFallback always returned aligned memory
    result = AllocateFallback(bytes);
  }
  assert((reinterpret_cast<uintptr_t>(result) & (align - 1)) == 0);
  return result;
}

char* Arena::AllocateNewBlock(size_t block_bytes) {
  char* result = new char[block_bytes];
  blocks_.push_back(result);
  // 更新 memory_usage_
  memory_usage_.fetch_add(block_bytes + sizeof(char*),
                          std::memory_order_relaxed);
  return result;
}

}  // namespace zhanmm
