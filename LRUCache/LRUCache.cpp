#include"LRUCache.h"
#include"Mutex.h"
#include<string>
#include<sys/time.h>
#include<stdint.h>
#include<iostream>

using namespace std;

namespace zhanmm {

long timeInSeconds(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec;
    // return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

LRUCache::LRUCache() : capacity(10), usage(0) {
  // Make empty circular linked lists.
  lru.next = &lru;
  lru.prev = &lru;
}


LRUCache::~LRUCache() {}


bool LRUCache::Set(const std::string& key,  const std::string& value,  int expire_time) {
    std::cout << "lick " << std::endl;
    MutexLocker lock(mutex);
    std::cout << "start Insert" << std::endl;
    return Insert(key, value, expire_time);
    
}

std::string LRUCache::Get(const std::string& key) {
    Entry* ret = Lookup(key);
    if (!ret) {
        std::cout << "ret null" << std::endl;
        return string("");
    }
    return ret->v.val->toString();
}



bool LRUCache::Insert(const string& key, const string& value, int expire_time) {
    std::cout << "Lru:" << capacity <<  std::endl;
    capacity = 1024*1024;
    assert(capacity > 0);
    //分配结点
    Entry* newEntry = new Entry(key, value);
    
    FinishErase(db.dict.Insert(newEntry));
    std::cout << "Insert rellay " << std::endl;
    LRUAppend(&lru, newEntry);
    usage += key.length();
    usage += value.length();

    if(expire_time != -1) {
        int64_t expireTime = timeInSeconds() + expire_time;
        Entry*  expireEntry = new Entry(newEntry->key, expireTime);
        FinishErase(db.expire.Insert(expireEntry));
    }

    if (usage > capacity) {
        LRUEliminate();
    }
    return true;
}


Entry* LRUCache::Lookup(const std::string& key) {
    Robj*  search =  new Robj(key);
    Entry*  t =  db.expire.Lookup(search);

    if (t) {
        std::cout << "time:" << t->v.s64 << " now:" << timeInSeconds() <<  std::endl;
        if (timeInSeconds() > t->v.s64) {
            Entry* del = db.dict.Lookup(search);
            std::cout << del->key->toString() << std::endl;
            FreeEntry(del);
            return nullptr;
        }
    }
    return db.dict.Lookup(search);
}


void LRUCache::LRUAppend(Entry* list, Entry* p) {
    p->next = list;
    p->prev = list->prev;
    p->prev->next = p;
    p->next->prev = p;
}


void LRUCache::LRURemove(Entry* p) {
    p->next->prev = p->prev;
    p->prev->next = p->next;
}

void LRUCache::LRUEliminate() {

    //当插入Key之后，发现所用空间> caapacity时，需要释放空间
    while (usage > capacity && lru.next != &lru) {
        Entry* old = lru.next;
        FreeEntry(old);
        usage -= old->key->len;
        usage -= old->v.val->len;
    }
}



void LRUCache::FreeEntry(Entry* del) {
    MutexLocker lock(mutex);
    LRURemove(del);
    std::cout << "Lru remove Finish" << std::endl; 
    Entry* dictDel = db.dict.Remove(del->key);
    std::cout << "dict remove Finish" << std::endl;
    Entry* expireDel = db.expire.Remove(del->key);
    std::cout << "expire remove Finish" << std::endl;
    FinishErase(dictDel);
    FinishErase(expireDel);
    std::cout << "Finish" << std::endl;
}


void LRUCache::FinishErase(Entry* p) {
    if (p) {
        delete p;
        p = nullptr;
    }
}

} //namespace zhanmm