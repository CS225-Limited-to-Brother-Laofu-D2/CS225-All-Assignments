// This file contains the class functions of CentralQueue and FibHeap

#include "FibHeap.h"

// Following are the functions of FibHeap
// constructor
template <class T> FibHeap<T>::FibHeap() {
    keyNum = 0;
    maxDegree = 0;
    min = nullptr;
    cons = nullptr;
}

// destructor
template <class T> FibHeap<T>::~FibHeap() { }

// remove a node from the double link list
template <class T> void FibHeap<T>::removeNode(FibNode<T> *node) {
    node->right->left = node->left;
    node->left->right = node->right;
}

// add a node to the left of the root
template <class T> void FibHeap<T>::addNode(FibNode<T> *node, FibNode<T> *root) {
    node->left        = root->left;
    node->right       = root;
    root->left->right = node;
    root->left        = node;
}

// insert a node to the fibheap
template <class T> void FibHeap<T>::insert(FibNode<T> *node) {
    // if the node is null then just return
    if (node == nullptr) return;
    // check whether there is any node in the fibheap
    // if so then insert the first node
    if (min == nullptr) min = node;
    else {
        addNode(node, min);
        if(min.key > node.key) min = node;
    }
    keyNum++;
    return;
}

// remove the min value node from the root list
template <class T> FibNode<T>* FibHeap<T>::extractMin() {
    FibNode<T> *ptr = min;

    if (ptr == ptr->right)
        min = nullptr;
    else
    {
        removeNode(ptr);
        min = ptr->right;
    }
    ptr->left = ptr->right = ptr;

    return ptr;
}

// link node to the root list
template <class T> void FibHeap<T>::link(FibNode<T>* node, FibNode<T>* root) {
    // remove node from the double link list
    removeNode(node);
    // set node as root's child
    if (root->child == nullptr)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

