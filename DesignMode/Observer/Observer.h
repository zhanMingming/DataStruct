#ifndef __MY_OBSERVER_H_
#define __MY_OBSERVER_H_
class Subject;
#include<string>

typedef std::string  STATE;
class Observer
{
  public:
  Observer()
  :nstate("")
  {}
  virtual ~Observer()
  {
  }

  virtual void update(Subject *pSubject)=0;
  protected:
  STATE nstate;
};

class ConcreateObserver:public Observer
{
   public:
   ConcreateObserver()
   :Observer()
   {}
  
   virtual ~ConcreateObserver()
   {}

   virtual void update(Subject *pSubject);
};

#endif
