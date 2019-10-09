#include"HashHandle.h"
#include"Entry.h"
#include<sys/time.h>
#include<iostream>


using namespace std;

namespace zhanmm {

HashHandle::HashHandle()
:rehash_idx(-1)
{
    table[0].Resize(8);
    std::cout << "resize" << std::endl;
}

HashHandle::~HashHandle() 
{}



Entry* HashHandle::Lookup(const Robj* key) {
    if (IsRehashing()) {
        Entry* p = table[1].Lookup(key);
        if (p) {
            return p;
        } else {
            p = table[0].Lookup(key);
        }
        return p;
    }

    return table[0].Lookup(key);
}



Entry* HashHandle::Insert(Entry* key) {
    std::cout << "HashHandle Insert" << std::endl;
    Entry *old = nullptr;
    if (IsRehashing()) {
        old = table[1].Insert(key);
        ReHash(1);   
    } else {
        old = table[0].Insert(key);
        if (table[0].NeedResize()) {
            Resize();
        }
    }
    return old;
} 


Entry* HashHandle::Remove(const Robj* key) {
    Entry* result = nullptr;
    if (IsRehashing()) {
        result = table[1].Remove(key);
        if (result) {
            return result;
        } else {
            result = table[1].Remove(key);
        }
        return result;
    }
    return table[0].Remove(key);
}



void HashHandle::Resize() {
    if (IsRehashing()) {
        return;
    }
    table[1].Resize(table[0].length_ * 2);
    rehash_idx = 0;
}


int  HashHandle::ReHash(int step) {

    if (rehash_idx < 0) return 0;
    while(step--) {

        
        if (table[0].elems_ == 0) {
            
            table[0].Free();

            table[0] = table[1];
            
            table[1].Reset();
            
            rehash_idx = -1;
            
            return 0;
        }

        assert(table[0].length_ > (uint32_t)rehash_idx);
        
        while(table[0].list_[rehash_idx] == nullptr)  rehash_idx++;
        
        Entry* p = table[0].list_[rehash_idx];
        
        while(p) {
            
            Entry* next = p->next_hash;
            

            table[1].Insert(p);
            
            --table[0].elems_;
        
            p = next;
        }

        table[0].list_[rehash_idx] = nullptr;
        rehash_idx++;
    }
    return 1;
}

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}
/*
 在给定毫秒数内，以 100 步为单位，对字典进行 rehash 。
*/
int HashHandle::ReHashMilliseconds(int ms) {
    // 记录开始时间
    long long start = timeInMilliseconds();
    int rehashes = 0;

    while(ReHash(100)) {
        rehashes += 100;
        // 如果时间已过，跳出
        if (timeInMilliseconds()-start > ms) break;
    }

    return rehashes;
}

}// namespace zhanmm

