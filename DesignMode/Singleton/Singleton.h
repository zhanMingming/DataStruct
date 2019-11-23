#ifndef __MY_SINGLETON_H_
#define __MY_SINGLETON_H_
#include<iostream>
class Singleton
{
  
  Singleton(){
  std::cout << "SINgleton()"<< std::endl;
  }

 //~Singleton(){}
public:
  static Singleton* GetInstancePtr();
  static Singleton GetInstance();

public:
  void Test();
   ~Singleton()
  {
    std::cout << "~Singleton()" << std::endl;
  }

private:
  static Singleton *m_pStatic;
};

#endif
