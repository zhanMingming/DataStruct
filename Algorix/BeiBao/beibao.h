#ifndef _MY_BEIBAO_H_
#define _MY_BEIBAO_H_
class Beibao
{
  public:
  Beibao(const char *filename);
  virtual ~Beibao();
   
  int MaxValue(int n,int m,int *w,int *v,int *c);
  void GetMaxValue();
  void Display();
  
  
  private:
  int maxValue;
  int m_nNumber;
  int m_nMaxWeight;

  int *m_pCount;
  int *m_pValue;
  int *m_pWeight;
};

#endif
