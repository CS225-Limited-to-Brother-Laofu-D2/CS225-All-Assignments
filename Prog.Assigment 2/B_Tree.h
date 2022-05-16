#include <iostream>
using namespace std;

template <typename T>
class BTreeNode
{
    bool is_leaf;// ture if is a leaf
    int size;// the size of number of keys 
    int depth;// its depth

    T *keys;// An array of keys
    //class of four pointers
    BTreeNode<T> **children;// An array of child pointers
public:

friend class BTree;
};

template <typename T>
class BTree
{
public:
    BTree(int x = 3);//constructor
    ~BTree();//destructor

    bool contain(T key) const;//if the key is in the tree
    T *getHandle(T key) const;
    void display() const;
    bool insert(T key);
    bool remove(T key);

private:
    void printNodeInfo(BTreeNode<T> *p_node) const;
    BTreeNode<T> *createEmptyNode();
   // void freeNode(BTreeNode<T> *p_node);
   // int findFirstNotSmaller(BTreeNode<T> *p_node, T a_key) const;
   void freeAll(BTreeNode<T> *p_node);
    T *search(BTreeNode<T> *p_node, T key_to_search) const;
    void display(BTreeNode<T> *p_node) const;
    void updateDepth(BTreeNode<T> *p_node);
    T getPred(BTreeNode<T> *p_node, int index) const;
    T getSucc(BTreeNode<T> *p_node, int index) const;
    bool insertToNode(BTreeNode<T> *p_node, T new_key);
    void splitChild(BTreeNode<T> *parent, int full_child_index);
    void mergeChildren(BTreeNode<T> *parent, int merge_index);
    bool removeFromLeaf(BTreeNode<T> *p_node, int remove_index);
    bool insertNonFull_recursively(BTreeNode<T> *p_node, T insert_key);
    // when the corresponding child has less than min_degree keys, try to fill the child with more key.
    void fillChild(BTreeNode<T> *parent, int fill_child_index);
    bool removeFromNonLeaf(BTreeNode<T> *&p_node, int remove_index);
    bool remove(BTreeNode<T> *&p_node, T remove_key);
    void borrowFromLeft(BTreeNode<T>* parent, int borrow_child_index);
    void borrowFromRight(BTreeNode<T>* parent, int borrow_child_index);

private:
    int min_degree;
    int key_num;
    BTreeNode<T> *root;
};