#include"Observer.h"
#include"Subject.h"
#include<iostream>
int main(void)
{
  Observer *p1=new ConcreateObserver;
  Observer *p2=new ConcreateObserver;
  Subject *s1=new ConcreateSubject;
  s1->Attach(p1);
  s1->Attach(p2);
  s1->SetState("hello");
  s1->Notify();
  s1->SetState("bitch");
  s1->Detach(p1);
  s1->Notify();
  delete s1;
}
 

   
