#ifndef CRYPTOPP_H
#define CRYPTOPP_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <string>
#include <cryptopp/hex.h>
#include <algorithm>

class Aes
{
public:
    static bool init(const std::string &key);
    static std::string encrypt(const std::string &inputPlainText);
    static std::string decrypt(std::string cipherTextHex);
private:
    static CryptoPP::byte s_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    //static byte s_iv[CryptoPP::AES::DEFAULT_KEYLENGTH];
};
#endif