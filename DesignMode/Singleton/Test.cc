#include<iostream>
#include"Singleton.h"
#include<memory>
int main(void)
{
   std::shared_ptr<Singleton>   p(Singleton::GetInstancePtr());

   
    std::cout << p.use_count() << std::endl;
    
    Singleton p3=Singleton::GetInstance();
    Singleton p4=Singleton::GetInstance();
    std::cout << &p3 << std::endl;
    std::cout << &p4 << std::endl;
    std::cout << p.use_count() << std::endl;
}

