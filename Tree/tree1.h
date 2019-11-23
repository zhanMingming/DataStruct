#ifndef __MY_TREE_H_
#define __MY_TREE_H_

#include<iostream>
struct BTnode
{
   int value;
   BTnode *plchild;
   BTnode *prchild;
};

class BiTree
{
   public:
   BiTree();
   ~BiTree();
   
   void CreateTree();
   void PreOrderTraverse();
   void InOrderTraverse();
   void PostOrderTraverse();

   void NoPreOrderTraverse();
   void NoInOrderTraverse();
   void NoPostOrderTraverse();
   
   void MiddleTraverse();
   void Convert_MiddleTraverse();
   int DepthOfTree_notrecursion();
   int DepthOfTree();
   int DepthOfTree2();
   void Destroy(); 
   
   void swap();//交换左右子树 
    
 private:
   BTnode *root;
};


#endif
