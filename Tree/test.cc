#include"tree1.h"
int main(void)
{
   BiTree b1;
   b1.CreateTree();

   std::cout << "NOInOrderTraverse "<< std::endl;
   b1.NoInOrderTraverse();
   std::cout << "NoPreOrderTraverse" << std::endl;
   b1.NoPreOrderTraverse();
   std::cout << "NoPostOrderTraverse" << std::endl;
   b1.NoPostOrderTraverse();
   std::cout << std::endl;


   std::cout << "the depth of tree is " << b1.DepthOfTree() << std::endl; 
  b1.MiddleTraverse();   

}


