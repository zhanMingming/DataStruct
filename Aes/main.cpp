/*
* @Author: zhanmingming
* @Date:   2019-11-07 17:25:30
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-11-08 11:46:01
*/
#include "Aes.h"
#include <iostream>

using namespace std;

int main() {

    // key 为密钥 
    std::string key = "5cfc975e3e40472e";
    Aes::init(key);
    std::string price = "1.5";
   
    std::string encode = Aes::encrypt(price);
    std::cout << encode << std::endl;
    std::cout << Aes::decrypt(encode) << std::endl;

    std::cout << Aes::decrypt("3b4f7f3461ddfa7d5b8f4640f2bbbed9") << std::endl;
}
