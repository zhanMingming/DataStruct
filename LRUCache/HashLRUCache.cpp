#include"HashLRUCache.h"
#include"Hash.h"

namespace zhanmm {

HashLRUCache::HashLRUCache(size_t capacity)
{
    const size_t per_capacity = (capacity + kNumShards - 1) / kNumShards;
    std::cout << per_capacity << std::endl;
    for (int index = 0; index < kNumShards; ++index) {
        shard[index].SetCapacity(per_capacity);
    }
}

bool HashLRUCache::Set(const std::string& key, const std::string& value, int expire_time = -1) {
    return shard[Shard(key)].Set(key, value, expire_time);
}

std::string HashLRUCache::Get(const std::string& key) {
    return  shard[Shard(key)].Get(key);
}

uint32_t HashLRUCache::Shard(const std::string& key) {
   return  (Hash(key.data(), key.size(), 0) & kNumShards);
}

} //namespace zhanmm



