#include<iostream>
#include"Creator.h"
#include"Product.h"
#include<memory>
std::shared_ptr<Product>   ConcreateCreator::ProductMethod()
{
   return  std::shared_ptr<Product>((new ConcreateProduct));
}
void Creator::AnOperation()
{
   std::shared_ptr<Product>  p=ProductMethod();
   std::cout << "an operation of product"<< std::endl;
}
ConcreateCreator::ConcreateCreator()
{
  std::cout << "construction of ConcreateCreator" << std::endl;
}

ConcreateCreator::~ConcreateCreator()
{
  std::cout << "Destruction of ConcreateCreator" << std::endl;
}

