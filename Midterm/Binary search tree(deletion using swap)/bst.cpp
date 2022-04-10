//
//  bst.cpp
//
//  Created by KD on 14.03.21.
//  Modified on 15.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bst.h"
using std::cout;
using std::cin;

/* the constructor creates a node with the given value and left and right pointers */

template<class T> node<T>::node(T item, node<T> *left, node<T> *right)
{
    data = item;
    pt_left = left;
    pt_right = right;
}

/* the get and set operations are obvious */
template<class T> T node<T>::getdata(void)
{
    return data;
}

template<class T> node<T> *node<T>::getleft(void)
{
    return pt_left;
}

template<class T> node<T> *node<T>::getright(void)
{
    return pt_right;
}

template<class T> void node<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void node<T>::setleft(node<T> *pt)
{
    pt_left = pt;
    return;
}

template<class T> void node<T>::setright(node<T> *pt)
{
    pt_right = pt;
    return;
}

template<class T> void node<T>::prettyprint(void)
{
    cout << "node(" << data << "): ";
    if (pt_left != 0)
        (*pt_left).pr_print();
    else
        cout << "(-)";
    cout << " -- " << data << " -- ";
    if (pt_right != 0)
        (*pt_right).pr_print();
    else
        cout << "(-)";
    cout << "\n";
    if (pt_left != 0)
        (*pt_left).prettyprint();
    if (pt_right != 0)
        (*pt_right).prettyprint();
    return;
}

template<class T> void node<T>::pr_print(void)
{
    cout << "(" << data << ")";
    return;
}

/* the constructor contains a trivial BST containing just a null pointer at the root */
template<class T> BST<T>::BST(void)
{
    root = 0;
}

/* the insert, delete and find functions are realised recursively starting from the root using the corresponding auxiliary functions */
template<class T> void BST<T>::insert(T item)
{
    root = _insert(root, item);
    return;
}

template<class T> void BST<T>::remove(T item)
{
    root = _delete(root, item);
    return;
}

template<class T> bool BST<T>::find(T item)
{
    return _find(root, item);
}

template<class T> node<T> *BST<T>::_insert(node<T> *pt, T val)
{
    if (pt == 0)
    /*  First check, if the root of the tree (given by the pointer pt) into which the value val is to be inserted is empty.
        In this case create and return a new node with the given value val and nullpointers for left and right successors. */
    {
        node<T> *newnode = new node<T>;
        (*newnode).setdata(val);
        return newnode;
    }
    /* Otherwise, we either have to insert into the left or right successor tree. In both cases the returned pointer pt_new will become the new value of the left or right successor pointer, resp. */
    if (val < (*pt).getdata())
    {
        node<T> *pt_new;
        pt_new = _insert((*pt).getleft(), val);
        (*pt).setleft(pt_new);
    }
    else if (val > (*pt).getdata())
    {
        node<T> *pt_new;
        pt_new = _insert((*pt).getright(), val);
        (*pt).setright(pt_new);
    }
    return pt;
}

template<class T> node<T> *BST<T>::_delete(node<T> *pt, T val)
{
    /* _delete searches recursively for the node with the given value val. If a nullpointer is reached, val does not appear in the BST, so no change is made.  */
    if (pt == 0)
        return pt;
    node<T> *pt_new;
    /* If the value val is found, it will be replaced by its direct successor. */
    if ((*pt).getdata() == val)
    {
        if ((*pt).getright() == 0)
            return (*pt).getleft();
        T succ = swap_successor((*pt).getright(), pt);
        (*pt).setdata(succ);
        return pt;
    }
    /* The recursive descent follows the left subtree or the right subtree. The call of _delete returns a pointer to the root of the modified tree. This must be returned and stored in the position (left or right) that issued the call.*/
    if (val < (*pt).getdata())
    {
        pt_new = _delete((*pt).getleft(), val);
        (*pt).setleft(pt_new);
    }
    else
    {
        pt_new = _delete((*pt).getright(), val);
        (*pt).setright(pt_new);
    }
    return pt;
}

/* _find works in the same way as _delete, but only a truth value is returned. */
template<class T> bool BST<T>::_find(node<T> *pt, T val)
{
    if (pt == 0)
        return false;
    if ((*pt).getdata() == val)
        return true;
    if (val < (*pt).getdata())
        return _find((*pt).getleft(), val);
    return _find((*pt).getright(), val);
}

template<class T> T BST<T>::swap_successor(node<T> *pt, node<T> *pt_parent)
{
    if ((*pt).getleft() == 0)
    {
        T successor = (*pt).getdata();
        if ((*pt_parent).getright() == pt)
            (*pt_parent).setright((*pt).getright());
        else
            (*pt_parent).setleft((*pt).getright());
        return successor;
    }
    return swap_successor((*pt).getleft(), pt);
}

/* Iterate through the tree, first the root, then the left subtree, then the right subtree. */
template<class T> void BST<T>::prettyprint(void)
{
    (*root).prettyprint();
    return;
}
