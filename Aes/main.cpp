/*
* @Author: zhanmingming
* @Date:   2019-11-07 17:25:30
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-11-07 19:00:33
*/
#include "Aes.h"
#include <iostream>

using namespace std;

int main() {

    std::string key = "cfc975e3e40472e8";
    Aes::init(key);
    std::string price = "1.5";
   
    std::string encode = Aes::encrypt(price);
    std::cout << encode << std::endl;
    std::cout << Aes::decrypt(encode) << std::endl;
}