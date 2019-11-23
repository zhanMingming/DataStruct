#include<algorithm>
#include"Subject.h"
#include<iostream>
#include"Observer.h"

void Subject::Attach(Observer *pObserver)
{  
    std::cout << "attach an Observer" << std::endl;
    m_listObserver.push_back(pObserver);
}
void Subject::Detach(Observer *pObserver)
{
    std::list<Observer *>::iterator iter;
    iter=std::find(m_listObserver.begin(),m_listObserver.end(),pObserver);
    if(iter != m_listObserver.end())
    {
      m_listObserver.erase(iter);
      std::cout << "detach an Observer" << std::endl;
    }else
    {
      std::cout << "not find this Observer" << std::endl;
    }
}

void Subject::Notify()
{
   std::list<Observer *>::iterator iter;
   for(iter=m_listObserver.begin();iter !=m_listObserver.end();++iter)
   {
       (*iter)->update(this);
   }
}
Subject::~Subject()
{
   std::list<Observer *>::iterator iter;
   for(iter=m_listObserver.begin();iter !=m_listObserver.end();++iter)
   {
       Observer *pObserver = *iter;
       delete pObserver;
   }
   m_listObserver.clear();
}

void ConcreateSubject::SetState(STATE nState)
{
   m_nSubjectState=nState;
}

STATE  ConcreateSubject::GetState()
{
   return  m_nSubjectState;
}

 
