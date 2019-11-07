/*
* @Author: zhanmingming
* @Date:   2019-11-07 17:25:23
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-11-07 19:05:10
*/
#include "Aes.h"
using namespace CryptoPP;
using namespace std;

byte Aes::s_key[CryptoPP::AES::DEFAULT_KEYLENGTH];

bool Aes::init(const std::string& key) {
    for (int index = 0; index < CryptoPP::AES::DEFAULT_KEYLENGTH; ++index) {
        s_key[index] = key[index];
    }
    return true;
}


std::string Aes::encrypt(const std::string&  plain) {
    //ECB_Mode< AES >::Encryption  encryptor( s_key, sizeof(s_key));
    
    std::string cipher, encoded;

    try {
        cout << "plain text: " << plain << endl;

    // ECB_Mode< AES >::Encryption e;
    // e.SetKey( key, key.size() );
        ECB_Mode< AES >::Encryption  encryptor( s_key, sizeof(s_key));

    // The StreamTransformationFilter adds padding
    //  as required. ECB and CBC Mode must be padded
    //  to the block size of the cipher.
        StringSource ss1( plain, true, 
            new StreamTransformationFilter( encryptor,
            new StringSink( cipher )
        ) // StreamTransformationFilter      
        ); // StringSource
    }catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }


    StringSource ss2( cipher, true,
        new HexEncoder(
            new StringSink( encoded )
        ) // HexEncoder
    ); // StringSource

    return encoded;

}


std::string Aes::decrypt(const std::string&  cipher) {

    string recovered, decoded;

    try {
        StringSource ss2( cipher, true,
            new HexDecoder(
                new StringSink( decoded )
            ) // HexEncoder
        ); // StringSource

        ECB_Mode< AES >::Decryption d(s_key, sizeof(s_key));
        // ECB Mode does not use an IV
        //d.SetKey( key, key.size() );

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource ss3( decoded, true, 
            new StreamTransformationFilter( d,
                new StringSink( recovered )
            ) // StreamTransformationFilter
        ); // StringSource

        cout << "recovered text: " << recovered << endl;
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }
    return recovered;

}