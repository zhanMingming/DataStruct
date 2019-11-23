#ifndef __MY_PRODUCT_H_
#define __MY_PRODUCT_H_

class Product
{
  public:
  Product()
  {}
  virtual ~Product()
  {}
};

class ConcreateProduct:public Product
{
  public:
  ConcreateProduct();
  virtual ~ConcreateProduct();
};


#endif

