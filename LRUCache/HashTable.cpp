#include"HashTable.h"
#include<stdint.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include"Hash.h"



using namespace std;

namespace zhanmm {

class Robj;

bool compartor(const Robj*x, const Robj* y) {
    return x->operator==(y);
}

HashTable::HashTable() : length_(0), elems_(0), list_(nullptr) {}
HashTable::~HashTable() { Free(); }


uint32_t HashTable::HashFunc(const Robj* key) {
    return Hash(key->data(), key->length(), 1024);
}


Entry* HashTable::Lookup(const Robj* key) {
    return *FindPointer(key);
}

Entry* HashTable::Insert(Entry* h) {
    std::cout << "hashTable:" << std::endl;
    std::cout << h->key->toString() << std::endl;
    Entry** ptr = FindPointer(h->key);

    std::cout << "hashTable2" << std::endl;
    Entry* old = *ptr;
    //如果*ptr != null, 则证明已有相同节点存在, 将*ptr 赋值为h 
    //如果*ptr == null, 则在末尾插入h 节点。
    h->next_hash = (old == nullptr ? nullptr : old->next_hash);   
    *ptr = h;
    
    // old 节点为空，代表没有相同节点，插入了新节点
    if (old == nullptr) {
        ++elems_;
        // if (elems_ > length_) {
        // // Since each cache entry is fairly large, we aim for a small
        // // average linked list length (<= 1).
        //     Resize();
        // }
    }
    
    return old;
}

Entry* HashTable::Remove(const Robj* key) {
    Entry** ptr = FindPointer(key);
    Entry* result = *ptr;
    if (result != nullptr) {
        *ptr = result->next_hash;
        --elems_;
    }
    return result;
}


Entry** HashTable::FindPointer(const Robj* key) {
    uint32_t hash = HashFunc(key);
    Entry** ptr = &list_[hash & (length_ - 1)];
    std::cout << "FindPointer " << std::endl;
    std::cout << "length_:" << length_ << std::endl;
    std::cout << "elems_:" << elems_ << std::endl;
    for(int index = 0; index < length_ ; ++index) {
        std::cout << list_[index] << std::endl;
    }
    std::cout << list_ << std::endl;
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;
    while ((*ptr != nullptr) && !(compartor((*ptr)->key, key))) {
        ptr = &(*ptr)->next_hash;
    }
    std::cout << ptr << std::endl;
    return ptr;
}


void HashTable::Reset() {
    length_ = 0;
    elems_ = 0;
    list_ = nullptr;
}

void HashTable::Resize(int size) {

    Entry** new_list = new Entry*[size];
    memset(new_list, 0, sizeof(new_list[0]) * size);
    std::cout << "resize:------" << std::endl;

    list_ = new_list;
    length_ = size;

    std::cout << length_ << std::endl;
}


void HashTable::Free() {

    //std::cout << "hashTable start Free" << std::endl;
    for (int index = 0; index < length_; ++index) {
        Entry *h = list_[index];
        while (h != nullptr) {
            Entry* next = h->next_hash;
            delete h;
            h = next;
        }
        list_[index] = nullptr;
    }
    if (list_) {
        delete[] list_;
    }
    list_ = nullptr;
}


} //namespace zhanmm

