#ifndef ZHANMM_LRUCACHE_H
#define ZHANMM_LRUCACHE_H


#include "HandleTable.h"
#include "Entry.h"
#include "Mutex.h"
#include "CacheOption.h"

#include<iostream>

namespace zhanmm {


const int MAX_KEY_LENGTH = 512;  //KB
const int MAX_VALUE_LENGTH = 1024; //KB

struct DB {
    DB(float load_factor)
    :expire_num(0), avg_ttl(0), slots(0)
    {
      dict = new HandleTable(load_factor);
      expire = new HandleTable(load_factor);
    }

    ~DB() {
      if (dict != nullptr) {
        std::cout << "dict~" << std::endl;
        delete dict;
        dict = nullptr;
      }

      if (expire != nullptr) {
        std::cout << "expire~" << std::endl;
        delete expire;
        expire = nullptr;
      }

    }
    
    uint32_t ExpireKeyNum() {
      return expire_num;
    }
    uint64_t AvgTtl() {
      return avg_ttl;
    }

    uint32_t Slots() {
      return slots;
    }

    HandleTable*  dict;
    HandleTable*  expire;
    uint32_t  expire_num; 
    uint64_t  avg_ttl;
    uint32_t  slots;

};


class LRUCache {
 public:
  LRUCache(CacheOption option);
  ~LRUCache();

  //void  SetCapacity(size_t capacity_) { capacity = capacity_; }

  bool  Set(const std::string& key,  const std::string& value, int expire_time = -1);
  
  std::string  Get(const std::string& key);

  int RandomRemoveExpireKey();

  size_t TotalCharge() const {
    return usage;
  }

  bool  ExpireKey(const std::string& key, int expire_time);

  int ExpireKeyNum() {
    return  db->ExpireKeyNum();
  }
  int Slots() {
    return db->Slots();
  }

private:

  // Like Cache methods, but with an extra "hash" parameter.
  bool Insert(const std::string& key, const std::string& value, int expire_time = -1);
  

  Entry* Lookup(const std::string& key);

  Entry* LookupWithNotCheckExpire(const std::string& key);

  bool DeleteKeyIfExpire(Entry* key);

  void LRURemove(Entry* e);

  void LRUAppend(Entry* list, Entry* e);

  void LRUEliminate(LruOption option);

  void FinishErase(Entry* e);

  void FreeEntry(Entry* e);

  // // Initialized before use.
  // size_t capacity;

  Mutex mutex;

  size_t usage; 

  Entry lru;

  DB *db;

  CacheOption option;
};


} // namespace zhanmm

#endif
