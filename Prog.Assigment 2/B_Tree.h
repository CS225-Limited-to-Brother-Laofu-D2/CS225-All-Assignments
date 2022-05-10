#ifndef BTREE_H
#define BTREE_H
using namespace std;
#include "Tuple.h"//The class head file


static const int m = 3;  
static const int key_max = 2*m-1;
static const int key_min = m - 1;
static const int child_max = key_max + 1;
static const int child_min = key_min + 1;

// Modified the B tree to hold Tuple.

class BTreeNode
{
 
public:
	BTreeNode(int _t, bool _leaf);//Constructor
    friend class BTree;
private:
    bool leaf;// True if it is a leaf
    int keyNum;//current number of keys
    BTreeNode* parent;
    BTreeNode* C[child_max];
    Tuple* keyvalue[key_max];// An array of keys
};
 

class BTree
{
public:
    BTree();
    bool _insert(Tuple* value);
    void SplitBlock(BTreeNode* node_parent,int child_index,BTreeNode* node_child);
    void Notfull_insert(BTreeNode* node,Tuple* value);
    bool contain(Tuple* value);

    void _printpoint(BTreeNode* node,int count);
    void printpoint(void);

    bool _delete(Tuple* value);
    BTreeNode* _find(BTreeNode* node,Tuple* value);
    void MergeBlock(BTreeNode* node_parent,int child_index);
    Tuple* getprev(BTreeNode* node);
    Tuple* getnext(BTreeNode* node);
    void BTree_deletebalance(BTreeNode* node,Tuple* value);

private:
	  BTreeNode* root;
};
#endif