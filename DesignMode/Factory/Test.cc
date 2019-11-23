#include"Product.h"
#include"Creator.h"
#include<iostream>
#include<memory>
int main(void)
{
  std::shared_ptr<Creator>  p(new ConcreateCreator);
  p->AnOperation();
  
} 
