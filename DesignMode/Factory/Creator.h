#ifndef __MY_CREATEOR_H_
#define __MY_CREATEOR_H_
#include<memory>
class Product;
class Creator
{
  public:
  Creator(){}
  virtual ~Creator()
  {}

  void AnOperation();

  protected:
  virtual std::shared_ptr<Product> ProductMethod()=0;
};

class ConcreateCreator:public Creator
{
  public:
  ConcreateCreator();
  virtual ~ConcreateCreator();
 
  protected:

  virtual std::shared_ptr<Product> ProductMethod();
};

#endif

