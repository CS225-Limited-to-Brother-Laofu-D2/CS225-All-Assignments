#include <iostream>
using namespace std;

template <typename T>
class BTreeNode
{
    bool is_leaf;// ture if is a leaf
    int size;// the size of number of keys 
    int depth;// its depth

    T *keys;// An array of keys
    BTreeNode<T> **children;// An array of child pointers
public:
BTreeNode(int _t, bool _leaf);   // Constructor
 
    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);
 
    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);
 
    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();
 
    // A function to search a key in the subtree rooted with this node.
    T *search(int key);   // returns NULL if key is not present.
// Make BTree friend of this so that we can access private members of this
// class in BTree functions
friend class BTree;
};

template <typename T>
class BTree
{
public:
    BTree(int x = 3);
    ~BTree();

    bool contain(T key) const;
    T *getHandle(T key) const;
    void display() const;
    bool insert(T key);
    bool remove(T key);

private:
    void printNodeInfo(BTreeNode<T> *p_node) const;
    BTreeNode<T> *createEmptyNode();
    void freeNode(BTreeNode<T> *p_node);
    int findFirstNotSmaller(BTreeNode<T> *p_node, T a_key) const;
    //T *search(BTreeNode<T> *p_node, T key_to_search) const;
    void freeAll(BTreeNode<T> *p_node);
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