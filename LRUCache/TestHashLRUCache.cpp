/*
* @Author: zhanmingming
* @Date:   2019-10-09 19:18:38
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-10-09 20:18:21
*/

#include "HashLRUCache.h"
#include<iostream>
#include<unistd.h>


using namespace std;
using namespace zhanmm;

int main() {
    HashLRUCache  cache(1024*1024);
    //cache.SetCapacity(1024*1024);
    string key = "wode";
    string value = "val";

    for(int i = 0; i < 10000; ++i) {
        string key1 = key + to_string(i);
        string value1 = value + to_string(i);
        std::cout << "begin" << std::endl;
        cache.Set(key1, value1, 100);
        std::cout << "totalCharge:" << cache.TotalCharge() << std::endl;
    }
    key = "wode";
    for (int i = 0; i < 10; ++i) {
        string key2 = key + to_string(i);
        std::cout << cache.Get(key2) << std::endl;
    }

    cache.Set("iam", "ming", 1);
    sleep(2);
    std::cout << cache.Get("iam") << std::endl;
    

}