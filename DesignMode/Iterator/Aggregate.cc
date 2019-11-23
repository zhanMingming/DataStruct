#include"Aggregate.h"
#include<iostream>
#include"Iterater.h"

ConcreateAggregate::ConcreateAggregate(int nSize)
:m_nSize(nSize),m_pData(NULL)
{
  m_pData=new DATA[nSize];

  for(int i=0;i<m_nSize;++i)
  {
    m_pData[i]=i;
  }
}
ConcreateAggregate::~ConcreateAggregate()
{
    delete []m_pData;
    m_pData=NULL;
}
int ConcreateAggregate::GetSize()
{
    return m_nSize;
}
Iterater * ConcreateAggregate::CreateIterater()
{
    return  new ConcreateIterater(this);
}
DATA ConcreateAggregate::GetItem(int nIndex)
{
    if(nIndex < m_nSize)
    {
       return m_pData[nIndex];
    }else
    {
       return -1;
    }
}




