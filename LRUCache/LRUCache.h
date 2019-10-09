#ifndef ZHANMM_LRUCACHE_H
#define ZHANMM_LRUCACHE_H


#include "HashHandle.h"
#include "Entry.h"
#include "Mutex.h"
#include<iostream>

namespace zhanmm {


struct DictDB {
    DictDB():expire_num(0) {}

    HashHandle  dict;
    HashHandle  expire;
    int  expire_num; 
};


class LRUCache {
 public:
  LRUCache();
  ~LRUCache();

  void  SetCapacity(size_t capacity_) { std::cout << "set:" << capacity_ << std::endl; capacity = capacity_;  std::cout << "s:" << capacity << std::endl;}

  bool  Set(const std::string& key,  const std::string& value, int expire_time = -1);
  
  std::string  Get(const std::string& key);

  size_t TotalCharge() const {
    return usage;
  }

private:

  // Like Cache methods, but with an extra "hash" parameter.
  bool Insert(const std::string& key, const std::string& value, int expire_time = -1);
  

  Entry* Lookup(const std::string& key);


  // size_t TotalCharge() const {
  //   return usage;
  // }

  void LRURemove(Entry* e);
  void LRUAppend(Entry* list, Entry* e);
  void LRUEliminate();
  void FinishErase(Entry* e);
  void FreeEntry(Entry* e);

  // Initialized before use.
  size_t capacity;

  Mutex mutex;

  size_t usage; 

  Entry lru;

  DictDB db;
};


} // namespace zhanmm

#endif
