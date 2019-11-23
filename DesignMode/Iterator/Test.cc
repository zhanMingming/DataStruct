#include"Iterater.h"
#include"Aggregate.h"
#include<iostream>
int main(void)
{
  Aggregate *p1=new ConcreateAggregate(4);
  Iterater *p2=new ConcreateIterater(p1);
  for(;false==p2->IsDone();p2->Next())
  {
     std::cout << p2->CurrentItem() << std::endl;
  }
 
  return 0;
}

