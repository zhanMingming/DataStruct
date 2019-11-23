#include"Iterater.h"
#include<iostream>
#include"Aggregate.h"

ConcreateIterater::ConcreateIterater(Aggregate *pAggregate)
:m_pConcreateAggregate(pAggregate),m_nIndex(0)
{}

void ConcreateIterater::First()
{
   m_nIndex=0;
}
void ConcreateIterater::Next()
{
   if(m_nIndex < m_pConcreateAggregate->GetSize())
   {
      ++m_nIndex;
   }
}
bool ConcreateIterater::IsDone()
{
   return m_nIndex==m_pConcreateAggregate->GetSize();
}
DATA ConcreateIterater::CurrentItem()
{
   return m_pConcreateAggregate->GetItem(m_nIndex);
}
ConcreateIterater::~ConcreateIterater()
{
}
 
