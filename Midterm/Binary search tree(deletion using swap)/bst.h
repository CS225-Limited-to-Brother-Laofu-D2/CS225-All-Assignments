//
//  bst.h
//
//  Created by KD on 14.03.21.
//  Modified on 15.04.21.
//

#ifndef bst_h
#define bst_h

template<class T> class BST;

template<class T> class node
{
    friend class BST<T>;
public:
    node(T item = 0, node<T> *left = 0, node<T> *right = 0);
    T getdata(void);
    node<T> *getleft(void);
    node<T> *getright(void);
    void setdata(T item);
    void setleft(node<T> *pt);
    void setright(node<T> *pt);
    void prettyprint(void);
    void pr_print(void);
private:
    T data;
    node<T> *pt_left;
    node<T> *pt_right;
};

template<class T> class BST
{
public:
    BST(void);
    void insert(T item);
    void remove(T item);
    bool find(T item);
    void prettyprint(void);
private:
    node<T> *root;
    /* _insert, _delete and _find are auxiliary functions to navigate recursively through the BST for insert, delete and find */
    node<T> *_insert(node<T> *pt, T val);
    node<T> *_delete(node<T> *pt, T val);
    bool _find(node<T> *pt, T val);
    /* merge is an auxiliary function used, when a non-leaf node is deleted */
    node<T> *merge(node<T> *pt1, node<T> *pt2);
    /* swap_successor is an auxiliary function to find the node with the successor key of the key that is to be deleted */
    T swap_successor(node<T> *pt, node<T> *pt_parent);
};

#endif /* bst_h */
