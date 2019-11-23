#include"tree1.h"
#include<queue>
#include<stack>

BiTree::BiTree()
:root(NULL)
{}
BTnode *Create_Tree()
{
   int val;
   std::cin >> val;
   BTnode *tree=NULL;
   if(val==0)
   {
     return NULL;
   }else
   {
     tree=new BTnode;
     tree->value=val;
     tree->plchild=Create_Tree();
     tree->prchild=Create_Tree();
    
     return tree;
   }
}

       
void BiTree::CreateTree()
{
    root=Create_Tree();
}
void Pre_Order_Traverse(BTnode *root)
{
   if(root != NULL)
   {
     std::cout << root->value << std::endl;
     Pre_Order_Traverse(root->plchild);
     Pre_Order_Traverse(root->prchild);
   }
}

void BiTree::PreOrderTraverse()
{
     Pre_Order_Traverse(root);
}

void InOrder_Traverse(BTnode *root)
{
     if(root != NULL)
     {
        InOrder_Traverse(root->plchild);
        std::cout << root->value << std::endl;
        InOrder_Traverse(root->prchild);
     }
}
void BiTree::InOrderTraverse()
{
      InOrder_Traverse(root);
}

void Post_Order_Traverse(BTnode *root)
{
     if(root != NULL)
     {
        Post_Order_Traverse(root->plchild);
        Post_Order_Traverse(root->prchild);
        std::cout << root->value << std::endl;
     }
}
void BiTree::PostOrderTraverse()
{
     Post_Order_Traverse(root);
}


void Middle_Traverse(BTnode *root)
{
   if(root==NULL)
   {
      return;
   }
   std::queue<BTnode *> obq;
   obq.push(root);
   while(obq.empty() != 1)
   {
       BTnode *pout=obq.front();
       obq.pop();
       std::cout << pout->value << std::endl;
       if(pout->plchild != NULL)
       {
           obq.push(pout->plchild);
       }
       if(pout->prchild != NULL)
       {
           obq.push(pout->prchild);
       }
   }
}

void BiTree::MiddleTraverse()
{
   Middle_Traverse(root);
}  
void No_PreOrderTraverse(BTnode *root)
{
    if(root==NULL)
    {
      return;
    }
    std::stack<BTnode *> obs;
    BTnode *tmp=root;
    while(tmp!=NULL || obs.empty() != 1)
    {
        while(tmp!=NULL)
        {
            obs.push(tmp);
            std::cout << tmp->value << std::endl;
            tmp=tmp->plchild;
        }
        if(obs.empty() !=1)
        {
             tmp=obs.top();
             obs.pop();
             tmp=tmp->prchild;
        }
     }
}
void BiTree::NoPreOrderTraverse()
{
    No_PreOrderTraverse(root);
}
void No_InOrderTraverse(BTnode *root)
{
    if(root==NULL)
    {
      return;
    }
    std::stack<BTnode *> obs;
    BTnode *tmp=root;
    while(tmp!=NULL||obs.empty() !=1)
    {
           while(tmp !=NULL)
           {
              obs.push(tmp);
              tmp=tmp->plchild;
           }
           if(obs.empty()!=1)
           {
               tmp=obs.top();
               std::cout << tmp->value << std::endl;
               obs.pop();
               tmp=tmp->prchild;
           }

    }
}

void BiTree::NoInOrderTraverse()
{
    No_InOrderTraverse(root);
}

void No_PostOrderTraverse(BTnode *root)
{
    if(root==NULL)
    {
       return;
    }
    BTnode *tmp=root;
    BTnode *pre=NULL;
    std::stack<BTnode *> obs;
    obs.push(tmp);
    while(obs.empty() != 1)
    {
       BTnode *current=obs.top();
    if((current->plchild == NULL&&current->prchild == NULL)||(pre!=NULL &&(pre==current->prchild || pre==current->plchild)))
     {
         std::cout << current->value << std::endl;
         obs.pop();
         pre=current;
     }else
     {
     if(current->prchild != NULL)
     {
         obs.push(current->prchild);
     }
     if(current->plchild != NULL)
     {
         obs.push(current->plchild);
     }
    
    }
   
   }
}
void BiTree::NoPostOrderTraverse()
{
    No_PostOrderTraverse(root);
}
int DepthOfTree(BTnode *root)
{
   int deep=0;
   if(root != NULL)
   {
       int depthoflchild=::DepthOfTree(root->plchild);
       int depthofrchild=::DepthOfTree(root->prchild);
       deep=(depthoflchild>depthofrchild)?(depthoflchild+1):(depthofrchild+1);
   }

   return deep;
}
int BiTree::DepthOfTree()
{
    return (::DepthOfTree(root));
}
#define MAXSIZE 30
int DepthOfTree2(BTnode *root)
{
    if(root==NULL)
    {
      return -1;
    }
    BTnode *array[MAXSIZE];
    int front=-1,rear=-1;
    int last=0,level=0;

    array[++rear]=root;
    while(front != rear)
    {
       BTnode *p=array[++front];
       if(p->plchild != NULL)
       {
           array[++rear]=p->plchild;
       }
       if(p->prchild != NULL)
       {
           array[++rear]=p->prchild;
       }
       if(front == last)
       {
            ++level;
            last=rear;
       }
    }
 return level;
}
void Convert_MiddleTraverse(BTnode *root)
{
    if(root == NULL)
    {
      return;
    }
    std::queue<BTnode *> obq;
    std::stack<BTnode *> obs;
    obq.push(root);
    while(obq.empty() != 1)
    {
        BTnode *tmp=obq.front();
        obq.pop();
        obs.push(tmp);
        if(tmp->plchild != NULL)
        {
            obq.push(tmp->plchild);
        }
        if(tmp->prchild != NULL)
        {
            obq.push(tmp->prchild);
        }
    }
    while(obs.empty() != 1)
    {
        BTnode *tmp=obs.top();
        obs.pop();
        std::cout << tmp->value << std::endl;
    }
}
void Convert_MiddleTraverse()
{
    ::Convert_MiddleTraverse(root);
}

      
     

        






   
int BiTree::DepthOfTree2()
{
     return (::DepthOfTree2(root));
}





                 
           

int DepthOfTree_notrecursion(BTnode *root)
{
    if(root == NULL)
    {
      return -1;
    }
    BTnode *tmp=root;
    
    std::queue<BTnode *> obs;
    obs.push(tmp);
    while(obs.empty() != 1)
    {
         tmp=obs.front();
         obs.pop();
     if(tmp->plchild != NULL)
     {
         obs.push(tmp->plchild);
     }
     if(tmp->prchild != NULL)
     {
         obs.push(tmp->prchild);
     }
    
    }
  
   int deep=0;
   BTnode *end=root;
   BTnode *begin=tmp;
   while(begin != end)
   {
         obs.push(end);
     while(obs.empty() != 1)
     {
        tmp=obs.front();
        obs.pop();
        if(tmp->prchild == begin || tmp->plchild == begin)
        {
            ++deep;
            begin=tmp;
            break;
        }
        if(tmp->plchild != NULL)
        {
           obs.push(tmp->plchild);
        }
        if(tmp->prchild != NULL)
        {
            obs.push(tmp->prchild);
        }
    }
   }
   
   return deep+1;
}
     
int BiTree::DepthOfTree_notrecursion()
{
  return  (::DepthOfTree_notrecursion(root));
}
void Destroy(BTnode *root)
{
   if(root != NULL)
   {
     Destroy(root->plchild);
     Destroy(root->prchild);
     delete root;
   }
}
void BiTree::Destroy()
{
    ::Destroy(root);
}
BiTree::~BiTree()
{
     this->Destroy();
}
void swap(BTnode *root)
{
      if(root != NULL)
      {
         swap(root->plchild);
         swap(root->prchild);
         BTnode *tmp=root->plchild;
         root->plchild=root->prchild;
         prchild=tmp;
      }
}
void BiTree::swap()
{
    ::swap(root);
}
    













 






      
         

 
     
  





     
       










 







   
        







   





    
     

 







      
   





    



  
    
   







 

 
 


             




   






        
 







        
          
   







    





       

 
 

  



     
