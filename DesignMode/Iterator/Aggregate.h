#ifndef __MY_AGGREGATE_H_
#define __MY_AGGREGATE_H_

typedef int DATA;
class Iterater;

class Aggregate
{
  public:
  Aggregate()
  {}
  
  virtual ~Aggregate()
  {}

  virtual Iterater * CreateIterater()=0;
  virtual int GetSize()=0;
  virtual DATA GetItem(int nIndex)=0;
};


class ConcreateAggregate:public Aggregate
{
  public:
  ConcreateAggregate(int nSize);
  virtual ~ConcreateAggregate();

  virtual Iterater * CreateIterater();
  virtual int GetSize();
  virtual DATA GetItem(int nIndex);

  private:
  int m_nSize;
  DATA *m_pData;
};

#endif
