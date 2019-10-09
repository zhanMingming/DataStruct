#ifndef ZHANMM_HASHLRUCACHE_H
#define ZHANMM_HASHLRUCACHE_H
#include"Cache.h"
#include"LRUCache.h"
#include<stdint.h>

namespace zhanmm {

const int  kNumShards = 16;

class HashLRUCache : public Cache {

public:
  HashLRUCache(size_t capacity);

  HashLRUCache(const HashLRUCache&) = delete;
  HashLRUCache& operator=(const HashLRUCache&) = delete;

  // Destroys all existing entries by calling the "deleter"
  // function that was passed to the constructor.
  ~HashLRUCache() {}

  bool Set(const std::string& key, const std::string& value, int expire_time);


  std::string Get(const std::string& key);


  size_t TotalCharge() const {
    size_t total = 0;
    for (int pos = 0; pos < kNumShards; ++pos) {
        total += shard[pos].TotalCharge();
    }
    return total;
  }

private:

   static uint32_t Shard(const std::string& key);


   LRUCache  shard[kNumShards];
   //uint64_t  last_id;
};

} //namespace zhanmm

#endif



