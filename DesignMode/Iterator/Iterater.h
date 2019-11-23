#ifndef __MY_ITERATER_H_
#define __MY_ITERATER_H_
typedef int DATA;
class Aggregate;

class Iterater
{
  public:

  Iterater()
  {}
  
  virtual ~Iterater()
  {}

  virtual void First()=0;
  virtual void Next()=0;
  virtual bool IsDone()=0;
  virtual DATA  CurrentItem()=0;
 
  private:
};

class ConcreateIterater:public Iterater
{
   public:
   ConcreateIterater(Aggregate *pAggregate);
  
   virtual ~ConcreateIterater();

   virtual void First();
   virtual void Next();
   virtual bool IsDone();
   virtual DATA CurrentItem();

   private:
   Aggregate *m_pConcreateAggregate;
   int m_nIndex;
};


#endif
