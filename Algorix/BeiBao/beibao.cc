#include"beibao.h"
#include<cstdio>
#include<cstdlib>
#include<iostream>
Beibao::Beibao(const char *filename)
:maxValue(0)
{
  FILE *fp=fopen(filename,"r");
  if(fp==NULL)
  {
    perror("open error");
  }
  
  fscanf(fp,"%d%d",&m_nNumber,&m_nMaxWeight);
  
  m_pCount=new int[m_nNumber+1];
  m_pValue=new int[m_nNumber+1];
  m_pWeight=new int[m_nNumber+1];

  m_pValue[0]=0;
  m_pWeight[0]=0;
 
  for(int index=0;index <= m_nNumber;++index)
  {
     m_pCount[index]=0;
  }
  
  for(int index=1;index <=m_nNumber;++index)
  {
     fscanf(fp,"%d",m_pWeight+index);
  }
  
  for(int index=1;index <=m_nNumber;++index)
  {
     fscanf(fp,"%d",m_pValue+index);
  }
  
  
  fclose(fp);
} 


int  Beibao::MaxValue(int n,int m,int *w,int *v,int *c)
{
   int row=n+1;
   int col=m+1;
   int i,j;
   int **value=new int*[row];
   for(i=0;i<row;++i)
   {
        value[i]=new int[col];
   }

#if 0   
int value[row][col];
#endif
   for(i=0;i<row;++i)
   {
       value[i][0]=0;
   }
   for(j=0;j<col;++j)
   {
       value[0][j]=0;
   } 
   for(i=1;i<row;++i)
   {
     for(j=1;j<col;++j)
     {
          value[i][j]=value[i-1][j];
          if(w[i]<=j)
          {
            int temp=value[i-1][j-w[i]]+v[i];
            if(temp>value[i][j])
            {
              value[i][j]=temp;
            }
          }
     }
   }
   j=m;
   for(i=n;i>0;--i)
   {
     if(value[i][j]>value[i-1][j])
     {
           c[i]=1;
           j-=w[i];
     }
   }
   
   int maxValue=value[n][m];
   return maxValue;

}

void Beibao::GetMaxValue()
{
  maxValue=MaxValue(m_nNumber,m_nMaxWeight,m_pWeight,m_pValue,m_pCount);
}
void Beibao::Display()
{
  for(int i=1;i<=m_nNumber;++i)
  {
     if(m_pCount[i])
     {
          std::cout << m_pWeight[i] << std::endl;
     }
  }
  
  std::cout << maxValue << std::endl;
}
Beibao::~Beibao()
{
  if(m_pCount)
  {
     delete []m_pCount;
     m_pCount=NULL;
  }
  if(m_pValue)
  {
     delete []m_pValue;
     m_pValue=NULL;
  }
  if(m_pWeight)
  {
     delete []m_pWeight;
     m_pWeight=NULL;
  }
}
 

  

 
     

       







   
