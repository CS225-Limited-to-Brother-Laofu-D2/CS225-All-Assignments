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

// merge Other into the current heap
template <class T> void FibHeap<T>::combine(FibHeap<T> *other) {
    if (other==NULL)
        return ;

    if(other->maxDegree > this->maxDegree) swap(*this, *other);

    if((this->min) == NULL) 
    { // this has no "minimum node"
        this->min = other->min;
        this->keyNum = other->keyNum;
        free(other->cons);
        delete other;
    }
    else if((other->min) == NULL)           
    { // this has "minimum node" && other Has no "minimum node"
        free(other->cons);
        delete other;
    }                                       
    else
    { // this has "minimum node" && other has "minimum node"
        // add "other root list "to "this"
        catList(this->min, other->min);

        if (this->min->key > other->min->key)
            this->min = other->min;
        this->keyNum += other->keyNum;
        free(other->cons);
        delete other;
    }
}

// Update Fibonacci heap node node with key
template <class T> void FibHeap<T>::update(FibNode<T> *node, T key) {
    if(key < node->key) decrease(node, key);
    else if(key > node->key) increase(node, key);
    else cout << "No need to update!!!" << endl;
}

// Whether there are key nodes in the Fibonacci heap
// Returns true if it exists, false otherwise
template <class T> bool FibHeap<T>::contains(T key) {
    return search(key)!=NULL ? true: false;
}

// remove the min value node from the root list
template <class T> FibNode<T>* FibHeap<T>::extractMin() {
    // ptr is a temporary variable
    FibNode<T> *ptr = min;
    
    if (ptr == ptr->right) min = nullptr;
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
    if (root->child == nullptr) root->child = node;
    else addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

// create the space required for consolidate
template <class T> void FibHeap<T>::makeCons() {
    int old = maxDegree;

    // calculate log2(keyNum), considering rounding up
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree) return ;

    // because the degree is maxDegree may be merged, so to maxDegree+1
    cons = (FibNode<T> **)realloc(cons, sizeof(FibHeap<T> *) * (maxDegree + 1));
}

// Merge trees of the same degree left and right in the root-linked table of the Fibonacci heap
template <class T> void FibHeap<T>::consolidate() {
    int i, degree, big_degree;
    FibNode<T> *x, *y;

    makeCons(); // create the space for hashing
    big_degree = maxDegree + 1;

    for (i = 0; i < big_degree; i++) cons[i] = nullptr;

    // merge root nodes of the same degree so that the tree of each degree is unique
    while (min != nullptr)
    {
        x = extractMin();                // fetch the smallest tree in the heap
        degree = x->degree;                    // get the degree of the smallest tree
        // cons[d] != NULL, means there are two trees with the same degree
        while (cons[degree] != nullptr)
        {
            y = cons[degree];                // y is a tree which has the same degree as x
            if (x->key > y->key) swap(x, y);       // ensure that the key value of x is smaller than y

            link(y, x);    // link y to x
            cons[degree] = nullptr;
            degree++;
        }
        cons[degree] = x;
    }
    min = nullptr;

    // re-add the nodes in cons to the root table
    for (i = 0; i < big_degree; i++)
    {
        if (cons[i] != nullptr)
        {
            if (min == nullptr) min = cons[i];
            else
            {
                addNode(cons[i], min);
                if ((cons[i])->key < min->key) min = cons[i];
            }
        }
    }
}

// remove the min node
template <class T> FibNode<T> *FibHeap<T>::popMin() {
    if (min==nullptr) return nullptr;

    FibNode<T> *child = nullptr;
    FibNode<T> *move = min;
    // add min's child and its brothers to the root list
    while (move->child != nullptr)
    {
        child = move->child;
        removeNode(child);
        if (child->right == child)
            move->child = nullptr;
        else
            move->child = child->right;

        addNode(child, min);
        child->parent = nullptr;
    }

    // remove m from the root list
    removeNode(move);
    // if m is the only node in the heap, set the smallest node of the heap to NULL
    // otherwise, set the smallest node of the heap to a non-empty node (m->right), and then adjust it.
    if (move->right == move)
        min = nullptr;
    
    else {
        min = move->right;
        consolidate();
    }
    keyNum--;

    return move;
}

// Get the minimum key value in the Fibonacci heap and save it to the pkey; success returns true, otherwise returns false.
template <class T> bool FibHeap<T>::minimum(T *ptr) {
    if (min==nullptr || ptr==nullptr)
        return false;

    *ptr = min->key;
    return true;
}

// update degrees
template <class T> void FibHeap<T>::renewDegree(FibNode<T> *parent, int degree) {
    parent->degree -= degree;
    if (parent-> parent != nullptr)
        renewDegree(parent->parent, degree);
}

// strips the node from the parent parent's child links, and make the node a member of the root list of the heap.
template <class T> void FibHeap<T>::cut(FibNode<T> *node, FibNode<T> *parent) {
    removeNode(node);
    renewDegree(parent, node->degree);
    // node has no brothers
    if (node == node->right)
        parent->child = nullptr;
    else
        parent->child = node->right;

    node->parent = nullptr;
    node->left = node->right = node;
    node->marked = false;
    // add the node tree to the root list
    addNode(node, min);
}


/*
 * do cascading cut to the node
 *
 * Cascade cut: If the reduced node breaks the minimal heap property
 * then it is cut down (i.e., removed from the bidirectional linked table it is in and
 * it is inserted into the two-way linked table formed by the root node of the minimum tree).
 * then recursively perform cascade pruning from the "parent node of the cut node" to the root node of the tree
 */
template <class T> void FibHeap<T>::cascadingCut(FibNode<T> *node) {
    FibNode<T> *parent = node->parent;
    if (parent != nullptr)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

// Add the Fibonacci heap node to key
template <class T>
void FibHeap<T>::increase(FibNode<T> *node, T key)
{
    FibNode<T> *child, *parent, *right;

    if (min==NULL ||node==NULL)
        return ;

    if (key <= node->key)
    {
        cout << "increase failed: the new key(" << key <<") "
             << "is no greater than current key(" << node->key <<")" << endl;
        return ;
    }

    // Will node every son (excluding grandchildren, great-grandchildren...) All added to the Fibonacci Heap root list
    while (node->child != NULL)
    {
        child = node->child;
        // Remove child from node's child list
        removeNode(child);               
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;
        // Add child to the root list
        addNode(child, min);       
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // If node is not in the root list,
    // Remove node from child link of parent node.
    // And make node a member of the root list of the heap,
    // Then perform "cascading clipping"
    // Otherwise, determine whether the smallest node of the heap needs to be updated
    parent = node->parent;
    if(parent != NULL)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    else if(min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(node->key > right->key)
                min = right;
            right = right->right;
        }
    }
}

// Decrease the value of node node in the Fibonacci heap to key
template <class T> void FibHeap<T>::decrease(FibNode<T> *node, T key) {
    FibNode<T> *parent;

    if (min == nullptr ||node == nullptr)
        return ;

    if ( key>=node->key)
    {
        // cout << "new key is greater than current key" << endl;
        return ;
    }

    node->key = key;
    parent = node->parent;
    if (parent != nullptr && node->key < parent->key)
    {
        // strip the node from its parent parent and add the node to the root chain table
        cut(node, parent);
        cascadingCut(parent);
    }

    // update the min node
    if (node->key < min->key)
        min = node;
}


// search the exact person recursively, according to the key and ID; if not find, return NULL
template <class T> FibNode<T>* FibHeap<T>::id_search(FibNode<T> *root, T key, int ID) {
    FibNode<T> *tmp = root;    // temporary node
    FibNode<T> *p = nullptr;    // target node

    if (root == nullptr)
        return root; // protect the stability

    do
    {
        if ((tmp->key == key) && (tmp->ID == ID))
        {
            p = tmp;
            break;
        }
        else
        {
            if ((p = id_search(tmp->child, key, ID)) != nullptr)
                break;
        }
        tmp = tmp->right;
    } while (tmp != root);

    return p;
}

// remove the node
template <class T> void FibHeap<T>::remove(FibNode<T> *node) {
    // set the key of the node to be the min
    T m = min->key-1;
    decrease(node, m-1);
    removeMin();
}

// following are functions of Centralized_Queue
