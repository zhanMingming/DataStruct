namespace zhanmm {



template<typename Key>
int  BTree<Key>::BinarySearch(Key* array, int start, int end, const Key& element) {
    while (start <= end) {
        int mid = (end + start) / 2;
        if (array[mid] == element) {
            return mid;
        } else if (array[mid] > element) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return start;
}


template<typename Key>
typename BTree<Key>::Node*  BTree<Key>::Search(const Key& element) {
    Node* node = root;
    while (node != nullptr) {
        int index = BinarySearch(node->m_key, 0, node->m_element_num - 1, element);
        
        //find node
        if (index < node->m_element_num && element == node->m_key[index]) {
            return node;
        // can't find node 
        }else if (node->m_leaf) {
            return nullptr;
        }
        node = node->m_child[index];
    }
    return nullptr;
}


template<typename Key>
void BTree<Key>::Insert(const Key& element) {
    if (Search(element)) {
        return;
    }
    if (root != nullptr && root->m_element_num == 2 * m_degree - 1) {
        Node * newNode = new Node();
        newNode->m_leaf = false;
        newNode->m_child = new Node*[1];
        newNode->m_child[0] = root;
        newNode->m_element_num = 0;
        root = newNode;

        SplitChild(root, 0);
    } 
    TraversalInsert(root, element);
    m_total_element_num++;
}


template<typename Key>
void BTree<Key>::TraversalInsert(Node* node, const Key& element) {
    int index = node->m_element_num - 1;
    // if node is leaf , insert element
    if (node->m_leaf) {
        node->m_key = (Key*)realloc(node->m_key, (node->m_element_num+1) * sizeof(Key));
        while(index >= 0 && element < node->m_key[index]) {
            node->m_key[index + 1] = node->m_key[index];
            --index;
        }
        node->m_key[index + 1] = element;
        ++node->m_element_num;
    } else {
        while (index >= 0 && element < node->m_key[index]) {
            --index;
        }
        ++index;
        if (node->m_child[index]->m_element_num == 2 * m_degree - 1) {
            SplitChild(node, index);
            if (element > node->m_key[index]) {
                ++index;
            }
        }
        TraversalInsert(node->m_child[index], element);
    }
}



// split parent->m_child[index] intto left node and right node
template<typename Key>
void  BTree<Key>::SplitChild(Node*  parent, int index) {
    
    Node* splitNode = parent->m_child[index];
    Node* left = new Node();
    Node* right = new Node();

    left->m_element_num = right->m_element_num = m_degree - 1;
    left->m_leaf = right->m_leaf = splitNode->m_leaf;
    left->m_key = new Key[m_degree - 1];
    right->m_key = new Key[m_degree - 1];
    for (int pos = 0; pos <= m_degree - 2; ++pos) {
        left->m_key[pos] = splitNode->m_key[pos];
        right->m_key[pos] = splitNode->m_key[pos + m_degree];
    }

    // handle child node
    if (!splitNode->m_leaf) {
        left->m_child = new Node*[m_degree];
        right->m_child = new Node*[m_degree];
        for (int pos = 0; pos < m_degree; pos++) {
            left->m_child[pos] = splitNode->m_child[pos];
            right->m_child[pos] = splitNode->m_child[pos + m_degree];
        }

    }


    // handle parent 
    parent->m_key = (Key*)realloc(parent->m_key,  (parent->m_element_num + 1) * sizeof(Key));
    parent->m_child = (Node**)realloc(parent->m_child, (parent->m_element_num + 2) * sizeof(Node*));
    
    for (int pos = parent->m_element_num - 1; pos >= index; --pos) {
        parent->m_key[pos + 1] = parent->m_key[pos];
    }

    // put the element splitNode->m_key[m_degree-1] into parent node
    parent->m_key[index] = splitNode->m_key[m_degree - 1];
    for(int pos = parent->m_element_num;  pos >= index + 1; --pos) {
        parent->m_child[pos + 1] = parent->m_child[pos];

    }

    // take left node and right node as the child node of parent node
    parent->m_child[index] = left;
    parent->m_child[index + 1] = right;

    parent->m_element_num++;
    FreeNode(splitNode);

}

template<typename Key>
void BTree<Key>::FreeNode(Node* deleteNode) {
    if (deleteNode->m_child) {
        delete[] deleteNode->m_child;
        deleteNode->m_child = nullptr;

    }
    if (deleteNode->m_key) {
        delete[] deleteNode->m_key;
        deleteNode->m_key = nullptr;
    }

    delete deleteNode;
}

template<typename Key>
void BTree<Key>::MergeNode(Node* & parent, int index, Node* & left, Node* & right) {
    left->m_key = (Key*)realloc(left->m_key, (2 * m_degree - 1) * sizeof(Key));
    for(int pos = 0; pos < m_degree - 1; ++pos) {
        left->m_key[pos + m_degree] = right->m_key[pos];
    }
    // if not leaf node, then need handle child
    if (!left->m_leaf) {
        left->m_child = (Node**)realloc(left->m_child, 2 * m_degree * sizeof(Node*));
        for (int pos = 0; pos < m_degree; ++pos) {
            left->m_child[pos + m_degree] = right->m_child[pos];
        }
    }
    // move parent->m_key[index] to left node
    left->m_key[m_degree-1] =  parent->m_key[index];
    left->m_element_num = 2 * m_degree - 1;

    /** handle parent */
    //delete parent->m_key[index] from parent
    for (int pos = index; pos < parent->m_element_num - 1; ++pos) {
        parent->m_key[pos] = parent->m_key[pos + 1];
    }
    //delete unnecessary space from m_key
    parent->m_key = (Key*)realloc(parent->m_key, (parent->m_element_num -1) * sizeof(Key));
    

    //delete parent.m_child[index+1] from parent
    for (int pos = index + 1; pos < parent->m_element_num; ++pos) {
        parent->m_child[pos] = parent->m_child[pos + 1];
    }
    // delete unnecessary sapce from m_child
    parent->m_child = (Node**)realloc(parent->m_child, (parent->m_element_num) * sizeof(Node*));
    
    parent->m_child[index] = left;
    --parent->m_element_num;

    // free right node
    FreeNode(right);

}


template<typename Key>
Key BTree<Key>::Precursor(Node* src) {
    while(!src->m_leaf) {
        src = src->m_child[src->m_element_num];
    }
    return  src->m_key[src->m_element_num - 1];
}

template<typename Key>
Key BTree<Key>::Successor(Node* src) {
    while(!src->m_leaf) {
        src = src->m_child[0];
    }
    return src->m_key[0];
}


// borrow  left node
// step 1: move parent->m_key[index] to target node
// step 2: move left->m_key[left->m_element_num-1]  to parent node
template<typename Key>
void BTree<Key>::BorrowElementFromLeftChild(Node* & parent, int index, Node* &left, Node* &target) {
    ++target->m_element_num;
    
    target->m_key = (Key*)realloc(target->m_key, target->m_element_num * sizeof(Key));
    for (int pos = target->m_element_num - 1;pos > 0; --pos) {
        target->m_key[pos] =  target->m_key[pos - 1];
    }
    // step 1
    target->m_key[0] = parent->m_key[index];
    // step 2
    parent->m_key[index] = left->m_key[left->m_element_num - 1];

    // if not leaf node, handle child
    if (!left->m_leaf) {
        target->m_child = (Node**)realloc(target->m_child, (target->m_element_num+1)*sizeof(Node*));
        for (int pos = target->m_element_num - 1; pos >= 0; --pos) {
            target->m_child[pos + 1] = target->m_child[pos];
        }
        target->m_child[0] = left->m_child[left->m_element_num];
        // delete unnecessary space
        left->m_child = (Node**)realloc(left->m_child, left->m_element_num * sizeof(Node*));

    }
    // delete unnecessary space
    --left->m_element_num;
    left->m_key = (Key*)realloc(left->m_key, left->m_element_num * sizeof(Key));

}

// borrow right node
// step1: move parent->m_key[index] to target node
// step2: move right->m_key[0] to parent node
template<typename Key>
void BTree<Key>::BorrowElementFromRightChild(Node* & parent, int index,  Node* &right, Node* &target) {
    ++target->m_element_num;
    target->m_key = (Key*)realloc(target->m_key, target->m_element_num * sizeof(Key));
    
    // step 1
    target->m_key[target->m_element_num - 1] = parent->m_key[index];
    // step 2
    parent->m_key[index] = right->m_key[0];
    
    //handle right  node
    for (int pos = 0; pos < right->m_element_num - 1; ++pos) {
        right->m_key[pos] = right->m_key[pos + 1];
    }
    //move m_child[0] of right Node to target Node
    if (!right->m_leaf) {
        target->m_child = (Node**)realloc(target->m_child, (target->m_element_num + 1) * sizeof(Node*));
        target->m_child[target->m_element_num] = right->m_child[0];
    
        for(int pos = 0; pos < right->m_element_num; ++pos) {
            right->m_child[pos] = right->m_child[pos + 1];
        }
        right->m_child = (Node**)realloc(right->m_child, right->m_element_num * sizeof(Node*));
        
    }
    --right->m_element_num;
    right->m_key = (Key*)realloc(right->m_key, right->m_element_num * sizeof(Key));
}


template<typename Key>
void BTree<Key>::TraversalDelete(Node* node, const Key& element) {
    
    // condition First
    if (node->m_leaf) {
        int index = 0;
        while (index < node->m_element_num && element > node->m_key[index]) {
            ++index;
        }
        for (int pos = index; pos < node->m_element_num - 1; ++pos) {
            node->m_key[pos] = node->m_key[pos + 1];
        }
        --node->m_element_num;
        node->m_key = (Key*)realloc(node->m_key, node->m_element_num * sizeof(Key));

    } else {
        int index = 0;
        while (index < node->m_element_num && element > node->m_key[index]) {
            ++index;
        }
        Node* targetChild= node->m_child[index];
        Node* rightChild = nullptr;
        if (index < node->m_element_num) {
            rightChild = node->m_child[index + 1];
        }
        // contidion Second (must have left and right child)
        if (element == node->m_key[index]) {
            // condition Second-a
            if (targetChild->m_element_num > m_degree - 1) {
                Key nearestLessElement = Precursor(targetChild);
                TraversalDelete(targetChild, nearestLessElement);
                node->m_key[index] = nearestLessElement;
            
            // condition Second-b
            } else if (rightChild && rightChild->m_element_num > m_degree-1) {
                
                Key nearestGreaterElement =  Successor(rightChild);
                TraversalDelete(rightChild, nearestGreaterElement);
                node->m_key[index] = nearestGreaterElement;
            
            // condition Second-c
            } else {
                MergeNode(node, index, targetChild, rightChild);
                TraversalDelete(targetChild, element);
            }
        // condition Third
        } else {
            Node* leftChild = nullptr;
            if (index > 0) {
                leftChild = node->m_child[index - 1];
            }
            // need to ensure number of element in targetChild  greater than m_degree-1
            if (targetChild->m_element_num == m_degree-1) {
                // condition Third-3a    
                if (leftChild && leftChild->m_element_num > m_degree-1) {
                    // borrow leftChild to targetChild
                    BorrowElementFromLeftChild(node, index - 1, leftChild, targetChild);
                    
                // condition Third-3a
                } else if (rightChild && rightChild->m_element_num > m_degree-1) {
                    // borrow rightChild to targetChild
                    BorrowElementFromRightChild(node, index, rightChild, targetChild);
                    
                // condition Third-3b
                } else if (leftChild) {
                    // merge targetChild to leftChild
                    MergeNode(node, index - 1, leftChild, targetChild);
                    targetChild = leftChild;
                // condition Third-3b
                } else {
                    // merge rightChild to targetChild
                    MergeNode(node, index, targetChild, rightChild);
                } 
                 
            }
            TraversalDelete(targetChild, element);
        }

    }
} 


template<typename Key>
void BTree<Key>::Delete(const Key& element) {
    if (!Search(element)) {
        return;
    }
    if (root->m_element_num == 1 && root->m_child == nullptr) {
        FreeNode(root);
        root = nullptr;
        m_total_element_num = 0;
        return;
    }

    if (root->m_element_num == 1) {
        Node* left = root->m_child[0];
        Node* right = root->m_child[1];
        if (left->m_element_num == m_degree - 1 && left->m_element_num == right->m_element_num) {
            MergeNode(root, 0, left, right);
            FreeNode(root);
            root = left;
        }
    }

    TraversalDelete(root, element);
    --m_total_element_num;
}

template<typename Key>
void BTree<Key>::TraversalFreeNode(Node* &node) {
    if (node->m_leaf) {
        delete node;
        node = nullptr;
    } else {
        for (int pos = 0; pos < node->m_element_num + 1; pos++) {
            TraversalFreeNode(node->m_child[pos]);
        }
        delete node;
        node = nullptr;
    }
}

template<typename Key>
void BTree<Key>::Print() const {
    typedef typename BTree<Key>::Node BNode;
    std::queue<BNode*> q;
    BNode* last = root;
    if (root) {
        q.push(root);
    }
    while (!q.empty()) {
        BNode* tmp = q.front();
        q.pop();
        if (!tmp->m_leaf) {
            std::cout << "|";
        }
        std::cout << "(";
        for (int pos = 0; pos <tmp->Size(); ++pos) {
            std::cout << tmp->m_key[pos];
            if (tmp->m_child && pos != tmp->Size() - 1) {
                std::cout << "|";
            }
        }
        std::cout << ")";
        if (!tmp->m_leaf) {
            std::cout << "|";
            for (int pos = 0; pos < tmp->Size() + 1; ++pos) {
                q.push(tmp->m_child[pos]);
            }
        }
        if (!last->m_leaf && tmp == last) {
            std::cout << std::endl;
            last = last->m_child[last->Size()];
        }
    }
    std::cout << std::endl;
}


} //namespace zhanmm


