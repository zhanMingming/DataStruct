#ifndef ZHANMM_BTREE_H
#define ZHANMM_BTREE_H

#include<queue>
#include<cstdlib>
typedef bool NodeKeyType;

namespace zhanmm {

template<typename Key>
class BTree {
public:    

    struct Node {

        Node(int element_num = 0):m_element_num(element_num), m_child(nullptr), m_key(nullptr), m_leaf(true){}
        ~Node() {
            if (m_child != nullptr) {
                delete []m_child;
                m_child = nullptr;
            }
            if (m_key != nullptr) {
                delete []m_key;
                m_key = nullptr;
            }
        }
        int Size() { return m_element_num; }

        // element
        Key *m_key; 
        
        // child pointer 
        struct Node **m_child;
        
        // is it a leaf node 
        NodeKeyType m_leaf;

        // number of elemnt int the Node
        int m_element_num;
    };

public:
    BTree(int degree=2):m_degree(degree) {
        root = new Node();
        m_total_element_num = 0;
    }
    ~BTree() {TraversalFreeNode(root);}
    
    Node*    Search(const Key& element);
    void     Insert(const Key& element);
    void     Delete(const Key& element);
    int      TotalSize() const { return m_total_element_num; };
    void     Print() const;
private:
    //  split child  parent->m_child[index]
    void    SplitChild(Node* parent, int index);
    void    TraversalInsert(Node *node, const Key& element);

   
    void    MergeNode(Node* & parent, int index, Node* & left, Node* & right);
    Key     Precursor(Node* src);
    Key     Successor(Node* src);
    void    BorrowElementFromLeftChild(Node* & parent, int index, Node* & left, Node* &target);
    void    BorrowElementFromRightChild(Node* & parent, int index, Node* & right, Node* &target);
    void    TraversalDelete(Node* parent, const Key& element);
    // free node and it's child node
    void    TraversalFreeNode(Node* &node);
    // only free this node
    void    FreeNode(Node* node);


private:
    // root Node 
    Node* root;
    
    // the number element of Node is [t-1, 2t-1]
    int m_degree;
    
    // the number of element
    int m_total_element_num;
};


}//namespace
#include"BTree.cpp"

#endif


