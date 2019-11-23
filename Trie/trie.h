#ifndef _MY_TRIE_H_
#define _MY_TRIE_H_
const int Num_chars=26;
class Trie
{
  public:
  Trie();
  virtual ~Trie();

  int  insert(const char *word,const char *number);
  int  search(const char *word,char *number);
    
  
  protected:
  struct Trie_node
  {
    Trie_node();
    char *data;
    Trie_node *num_char[Num_chars];
  };
  
  private:
  Trie_node *root;
};


#endif
