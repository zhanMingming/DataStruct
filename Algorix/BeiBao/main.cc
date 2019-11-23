#include"beibao.h"
#include<iostream>
int main(int argc,char **argv)
{
  Beibao bao1(argv[1]);
  bao1.GetMaxValue();
  bao1.Display();
}

