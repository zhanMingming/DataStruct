#include"trie.h"
#include<iostream>
int main(void)
{
  Trie t1;
  t1.insert("zhanMingming","18826486968");
  t1.insert("hanfeigan","12345678901");
  t1.insert("wodehaoma","12345679862");
  
  char number[12];
  if(t1.search("zhanMingming",number))
  {
     std::cout << "find it " << std::endl;
     std::cout << number << std::endl;
  }
  
}
         
