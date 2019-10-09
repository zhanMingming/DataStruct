#ifndef ZHANMM_HASHHANDLE_H
#define ZHANMM_HASHHANDLE_H

#include"Entry.h"
#include"HashTable.h"


namespace zhanmm {

class HashHandle {
 public:
  HashHandle();
  ~HashHandle();

  Entry* Lookup(const Robj* key);
  Entry* Insert(Entry *key);

  Entry* Remove(const Robj* key);

 private:
  bool  IsRehashing() {
    return rehash_idx != -1;
  }

  void Resize();

  int ReHash(int step);
  
  int ReHashMilliseconds(int ms);

  // // 哈希表长度
  // uint32_t length_;
  // // 哈希表节点个数
  // uint32_t elems_;

  int32_t  rehash_idx;

  HashTable  table[2];

};
 
} //namespace zhanmm

#endif
