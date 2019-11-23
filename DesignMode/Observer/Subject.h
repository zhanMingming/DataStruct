#ifndef __MY_SUBJECT_H_
#define __MY_SUBJECT_H_
#include<list>
#include<string>
class Observer;
typedef std::string  STATE;
class Subject
{
   public:
   Subject()
   :m_nSubjectState("")
   {}
   virtual ~Subject();
   void Notify();
   void Attach(Observer *pObserver);
   void Detach(Observer *pObserver);
   virtual void SetState(STATE nState)=0;
   virtual STATE GetState()=0;



   protected:
   STATE m_nSubjectState;
   std::list<Observer *>  m_listObserver;
};

class ConcreateSubject:public Subject
{
   public:
   ConcreateSubject()
   :Subject()
   {}
  
   virtual ~ConcreateSubject()
   {}

   virtual void SetState(STATE nState);
   virtual STATE GetState();


};

#endif
