#include"trie.h"
#include<cstring>
#include<iostream>
Trie::Trie()
:root(NULL)
{}

Trie::Trie_node::Trie_node()
{
  data=NULL;
  for(int index=0;index <Num_chars;++index)
  {
        num_char[index]=NULL;
  }
  
}
Trie::~Trie()
{
}

int Trie::insert(const char *word,const char *number)
{
    if(word==NULL||number==NULL)
    {
         std::cout << "insert error" << std::endl;
         return 0;
    }
    if(strlen(number) > 11)
    {
         std::cout << "the number is overlength" << std::endl;
         return 0;
    }
    
    if(root==NULL)
    {
       root=new Trie_node;
    }
    Trie_node *location=root;
    char char_code;
    while(location != NULL && *word !=0)
    {
       if(*word >='A'&& *word <='Z')
       {
         char_code=*word-'A';
       }else if(*word>='a'&& *word<='z')
       {
         char_code=*word-'a';
       }else
       {
         return 0;
       }
       if(location->num_char[char_code]==NULL)
       {
           location->num_char[char_code]=new Trie_node;
       }
       location=location->num_char[char_code];
       ++word;
    }
    
     location->data=new char[strlen(number)];
      
     strcpy(location->data,number);
     return 1;     
}
int Trie::search(const char *word,char *number)
{
      if(word == NULL)
      {
          return 0;
      }
      char char_code;
      Trie_node *location=root;
      while(location != NULL && *word !=0)
      {
         if(*word >='A' && *word <='Z')
         {
           char_code=*word-'A';
         }else if(*word>='a'&& *word<='z')
         {
            char_code=*word-'a';
         }else
         {
            return 0;
         }

   
        if(location->num_char[char_code]==NULL)
        {
            return 0;
        }
        location=location->num_char[char_code];
       
        ++word;
     }
     
     if(location != NULL && location->data != NULL)
     {
         strcpy(number,location->data);
         return 1;
     }else
     {
         return 0;
     }
}


               
     
        


     

    
                   
 




 

   




  
   
    
             





        
