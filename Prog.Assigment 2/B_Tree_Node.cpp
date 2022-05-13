#pragma once
#include "B_Tree.h"
using namespace std;


 

// Function to search key in subtree rooted with this node
template <typename T>
T *BTreeNode<T>::search(int key)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;
 
    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;
 
    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;
 
    // Go to the appropriate child
    return C[i]->search(k);
}