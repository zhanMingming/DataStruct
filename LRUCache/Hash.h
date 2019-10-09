#ifndef ZHANMM_HASH_H
#define ZHANMM_HASH_H
#include<stdio.h>
#include<stdint.h>

namespace zhanmm {

uint32_t Hash(const char* data, size_t n, uint32_t seed);


} //namespace zhanmm

#endif
