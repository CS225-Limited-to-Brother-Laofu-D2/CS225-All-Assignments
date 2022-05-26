//
//  lgraphtraversal.cpp
//  
//
//  Created by KD on 12.04.21.
//  Modified on 08.05.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "lgraph.h"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

template<class T> fifo<T>::fifo(int size)
{
    maxsize = size;
    if (size < 10)
        minsize = size;
    else
        minsize = 10;
    numitems = 0;
    first = 0;
    last = -1;
    reprarray = new T[maxsize];
}

template<class T> T &fifo<T>::operator[](int index)
{
    if ((1 <= index) && (index <= numitems))
    {
        int relindex = (index + first -1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "Error: index " << index << " out of range.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> int fifo<T>::getlength(void)
{
    return numitems;
}

template<class T> bool fifo<T>::isempty(void)
{
    if (numitems == 0)
        return true;
    else
        return false;
}

template<class T> T fifo<T>::front(void)
{
    if (isempty() == false)
        return reprarray[first];
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> T fifo<T>::back(void)
{
    if (isempty() == false)
    {
        int relindex = (first + numitems - 1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::pushback(T value)
{
    if (numitems == maxsize)
        allocate();
    last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

template<class T> T fifo<T>::popfront(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false)
    {
        T frontelement = reprarray[first];
        first = ++first % maxsize;
        --numitems;
        return frontelement;
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

template<class T> void fifo<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
}

template<class T> void AList<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T AList<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::concat(AList<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool AList<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool AList<T>::equal(AList<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool AList<T>::sublist(AList<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

template<class T> void AListsort<T>::bsort(void)
{
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;
    for (int i = 0; i < numitems - 1; ++i)
    {
        for (int j = i+1; j < numitems; ++j)
        {
            if (reprarray[i] > reprarray[j])
            {
                T temp;
                temp = reprarray[i];
                reprarray[i] = reprarray[j];
                reprarray[j] = temp;
            }
        }
    }
    return;
}

template<class T> void AListsort<T>::qsort(int thr)
{
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;
    if (thr < 20)
        thr = 20;
    if (thr > 100)
        thr = 100;
    if (numitems <= thr)
    {
        bsort();
        return;
    }
    else
    {
        srand(time(0));
        int index = rand() % numitems;
        T pivot = reprarray[index];
        AListsort<T> lsmall = AListsort<T>(10);
        AListsort<T> lpivot = AListsort<T>(5);
        AListsort<T> llarge = AListsort<T>(10);
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] < pivot)
                lsmall.append(reprarray[i]);
            else if (reprarray[i] == pivot)
                lpivot.append(reprarray[i]);
            else
                llarge.append(reprarray[i]);
        }
        lsmall.qsort(thr);
        llarge.qsort(thr);
        for (int i = 0; i < numitems; ++i)
        {
            if (i < lsmall.getlength())
                reprarray[i] = lsmall.getitem(i+1);
            else if (i < (lsmall.getlength() + lpivot.getlength()))
                reprarray[i] = lpivot.getitem(i - lsmall.getlength() + 1);
            else
                reprarray[i] = llarge.getitem(i - lsmall.getlength() - lpivot.getlength() + 1);
        }
        return;
    }
}

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, i.e. the list of neighbour vertices. */
template<class T, class L> vertex<T,L>::vertex(T item, vertex<T,L> *pt_next, vertex<T,L> *pt_prev)
{
    vertexid = item;
    next = pt_next;
    previous = pt_prev;
    edgelist = 0;
}

template<class T, class L> int vertex<T,L>::numoutedges(void)
{
    if (edgelist != 0)
        return (*edgelist).getlength();
    return 0;
}

template<class T, class L> T vertex<T,L>::getitem(void)
{
    return vertexid;
}

template<class T, class L> vertex<T,L> * vertex<T,L>::getnext(void)
{
    return next;
}

template<class T, class L> vertex<T,L> * vertex<T,L>::getprevious(void)
{
    return previous;
}

template<class T, class L> elist<T,L> * vertex<T,L>::getedges(void)
{
    return edgelist;
}

template<class T, class L> void vertex<T,L>::setitem(T item)
{
    vertexid = item;
    return;
}

template<class T, class L> void vertex<T,L>::setnext(vertex<T,L> *pt_next)
{
    next = pt_next;
    return;
}

template<class T, class L> void vertex<T,L>::setprevious(vertex<T,L> *pt_prev)
{
    previous = pt_prev;
    return;
}

template<class T, class L> void vertex<T,L>::setedges(elist<T,L> *pt_edges)
{
    edgelist = pt_edges;
    return;
}

/* A vertexlist is a doubly linked list with vertices and a dummy node. */
template<class T, class L> vertexlist<T,L>::vertexlist(void)
{
    dummy = new vertex<T,L>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numvertices = 0;
}

template<class T, class L> int vertexlist<T,L>::getlength(void)
{
    return numvertices;
}

/* For counting edges we must add up the counts of outgoing edges for each vertex */
template<class T, class L> int vertexlist<T,L>::countedges(void)
{
    int count = 0;
    vertex<T,L> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        count = count + (*pt).numoutedges();
        pt = (*pt).getnext();
    }
    return count;
}

/* append is analogous to linked lists, i.e. we add a new vertex at the end and adjust pointers. */
template<class T, class L> void vertexlist<T,L>::append(T item)
{
    vertex<T,L> * pt_last = (*dummy).getprevious();
    vertex<T,L> * pt_new = new vertex<T,L>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(dummy);
    (*pt_new).setprevious(pt_last);
    (*dummy).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++numvertices;
    return;
}

/* A new vertex is only added, if it is not yet in the list. */
template<class T, class L> void vertexlist<T,L>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

/* To check if a vertex is already in the list the list is scanned until the element is found. */
template<class T, class L> bool vertexlist<T,L>::contains(T item)
{
    bool result = false;
    vertex<T,L> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

/* In order to remove a vertex we have to find it in the list of vertices. If it has a non-empty list of neighbours, it cannot be deleted. It cannot be deleted, if it appears in any edgelist. */
template<class T, class L> bool vertexlist<T,L>::remove(T item)
{
    bool result = false;
    vertex<T,L> * location = 0;
    vertex<T,L> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            if ((*pt).getedges() != 0)
            {
                cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
                return result;
            }
            /* We may be able to delete the vertex at location pt, but we still have to check other edgelists. Therefore pt is stored in location. */
            location = pt;
            continue;
        }
        elist<T,L> * edges = (*pt).getedges();
        if (edges != 0 && (*edges).contains(item) == true)
            /* if is appears in an edgelist, there is no delete. */
        {
            cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
            return result;
        }
        pt = (*pt).getnext();
    }
    /* Finally, we get to the deletion from the veertexlist. */
    if (location != 0)
    {
        result = true;
        vertex<T,L> * pt_prev = (*location).getprevious();
        vertex<T,L> * pt_next = (*location).getnext();
        (*pt_prev).setnext(pt_next);
        (*pt_next).setprevious(pt_prev);
        --numvertices;
    }
    /* The returned Boolean result indicates, if the vertex was deleted or not. */
    return result;
}

/* Adding an edge is done by first locating the origin vertex in the vertex list, then inserting the destination vertex into the associated edgelist. */
template<class T, class L> void vertexlist<T,L>::addedge(T first, T second, L label)
{
    vertex<T,L> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T,L> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).addvertex(second, label);
            else
            {
                elist<T,L> * newlist = new elist<T,L>(second, label);
                (*pt).setedges(newlist);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    /* If the origin vertex is not yet in the vertex list, it is first appended to the vertex list. The associated edgelist contains a single vertex. */
    append(first);
    pt = (*dummy).getprevious();
    elist<T,L> * newlist = new elist<T,L>(second, label);
    (*pt).setedges(newlist);
    return;
}

/* Removing an edge is done by first locating the origin vertex in the vertex list, then searching for the destination vertex into the associated edgelist. In this case the edge is always deleted, if it is found. */
template<class T, class L> void vertexlist<T,L>::removeedge(T first, T second)
{
    vertex<T,L> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T,L> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
            {
                (*pt_edges).remove(second);
                if ((*pt_edges).getlength() == 0)
                    (*pt).setedges(0);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

template<class T, class L> elist<T,L> * vertexlist<T,L>::edges(T node)
{
    vertex<T,L> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == node)
            return (*pt).getedges();
        pt = (*pt).getnext();
    }
    return 0;
}

/* To build list of outgoing edges for a given vertex, a new edge sequence is created for the output, then by scanning the associated edgelist edges (pairs of vertices) are added one by one. */
template<class T, class L> edgelist<T,L> * vertexlist<T,L>::outgoingedges(T item)
{
    edgelist<T,L> * result = new edgelist<T,L>;
    vertex<T,L> * ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*ptv).getitem() == item)
        {
            elist<T,L> * edges = (*ptv).getedges();
            if (edges != 0)
                (*edges).addall(item, result);
            return result;
        }
        ptv = (*ptv).getnext();
    }
    return result;
}

/* only for testing */
template<class T, class L> void vertexlist<T,L>::prettyprint(void)
{
    vertex<T,L> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Edges with origin " << (*ptv).getitem() << " :\n";
        edgelist<T,L> * pte = outgoingedges((*ptv).getitem());
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }
    return;
}

/* The edge list for each vertex is organised analogous to the vertexlist, but the are no associated edgelists. The elements of the list are organised by the neighbour class. */
template<class T, class L> neighbour<T,L>::neighbour(T item, L lab, neighbour<T,L> *pt_next, neighbour<T,L> *pt_prev)
{
    secondvertex = item;
    label = lab;
    next = pt_next;
    previous = pt_prev;
}

template<class T, class L> T neighbour<T,L>::getitem(void)
{
    return secondvertex;
}

template<class T, class L> L neighbour<T,L>::getlabel(void)
{
    return label;
}

template<class T, class L> neighbour<T,L> * neighbour<T,L>::getnext(void)
{
    return next;
}

template<class T, class L> neighbour<T,L> * neighbour<T,L>::getprevious(void)
{
    return previous;
}

template<class T, class L> void neighbour<T,L>::setitem(T item)
{
    secondvertex = item;
    return;
}

template<class T, class L> void neighbour<T,L>::setlabel(L lab)
{
    label = lab;
    return;
}

template<class T, class L> void neighbour<T,L>::setnext(neighbour<T,L> * pt)
{
    next = pt;
    return;
}

template<class T, class L> void neighbour<T,L>::setprevious(neighbour<T,L> * pt)
{
    previous = pt;
    return;
}

/* elist is the class used for the representation of doubly linked lists of vertices (no dummy node) associated with the vertices in the vertexlist. All functions are analogous to those defined for vertexlist. */
template<class T, class L> elist<T,L>::elist(T item, L label)
{
    first = new neighbour<T,L>;
    (*first).setitem(item);
    length = 1;
    (*first).setlabel(label);
    (*first).setnext(first);
    (*first).setprevious(first);
}

template<class T, class L> int elist<T,L>::getlength(void)
{
    return length;
}

template<class T, class L> neighbour<T,L> * elist<T,L>::getfirst(void)
{
    return first;
}

template<class T, class L> void elist<T,L>::append(T item, L label)
{
    neighbour<T,L> * pt_last = (*first).getprevious();
    neighbour<T,L> * pt_new = new neighbour<T,L>;
    (*pt_new).setitem(item);
    (*pt_new).setlabel(label);
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    return;
}

template<class T, class L> void elist<T,L>::addvertex(T item, L label)
{
    if (contains(item) == false)
        append(item, label);
    return;
}

template<class T, class L> bool elist<T,L>::contains(T item)
{
    bool result = false;
    neighbour<T,L> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

template<class T, class L> void elist<T,L>::remove(T item)
{
    neighbour<T,L> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            neighbour<T,L> * pt_prev = (*pt).getprevious();
            neighbour<T,L> * pt_next = (*pt).getnext();
            (*pt_prev).setnext(pt_next);
            (*pt_next).setprevious(pt_prev);
            if (i == 0)
                first = pt_next;
            --length;
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}
/* The function addall adds all pairs with the given item and the list members, i.e. all outgoing edges to the list given by the pointer pt. It exploit the function add on edgelists. */
template<class T, class L> void elist<T,L>::addall(T item, edgelist<T,L> *pt)
{
    neighbour<T,L> * pte = first;
    for (int i = 0; i < length; i++)
    {
        (*pt).add(item, (*pte).getitem(), (*pte).getlabel());
        pte = (*pte).getnext();
    }
    return;
}

/* Edges are simply pairs of vertices with obvious get and set functions. */
template<class T, class L> edge<T,L>::edge(T first, T second, L value)
{
    firstitem = first;
    seconditem = second;
    label = value;
}

template<class T, class L> T edge<T,L>::origin(void)
{
    return firstitem;
}

template<class T, class L> T edge<T,L>::destination(void)
{
    return seconditem;
}

template<class T, class L> L edge<T,L>::getlabel(void)
{
    return label;
}

template<class T, class L> void edge<T,L>::setorigin(T item)
{
    firstitem = item;
    return;
}

template<class T, class L> void edge<T,L>::setdestination(T item)
{
    seconditem = item;
    return;
}

template<class T, class L> void edge<T,L>::setlabel(L value)
{
    label = value;
    return;
}

/* only for testing */
template<class T, class L> void edge<T,L>::prettyprint(void)
{
    cout << "(origin: " << origin() << ", destination: " << destination() << ", label: " << getlabel() << ")\n";
    return;
}

/* edgelists, i.e. sequences of pairs of vertices are only used for output purposes. */
template<class T, class L> edgelist<T,L>::edgelist(void)
{
    reprarray = new edge<T,L>*[10000];
    numedges = 0;
}

template<class T, class L> int edgelist<T,L>::getnumedges(void)
{
    return numedges;
}

template<class T, class L> void edgelist<T,L>::add(T item1, T item2, L label)
{
    edge<T,L> * newedge = new edge<T,L>(item1,item2,label);
    reprarray[numedges] = newedge;
    ++numedges;
    return;
}

template<class T, class L> void edgelist<T,L>::prettyprint(void)
{
    for (int i = 0; i < numedges; i++)
    {
        edge<T,L> * pte = reprarray[i];
        (*pte).prettyprint();
    }
    cout << "      --------\n";
    return;
}

/* Until here there was no change to the corresponding classes used for undirected graphs. Now define directed labelled graphs. The only change is that for insertion of an edge (v,w) there is no insertion of (w,v). Analogous for edge deletion. */

/* A labelled digraph object just contains a pointer to a vertexlist. */
template<class T, class L> ldigraph<T,L>::ldigraph(void)
{
    vertices = new vertexlist<T,L>;
}

template<class T, class L> int ldigraph<T,L>::numvertices(void)
{
    return (*vertices).getlength();
}

template<class T, class L> int ldigraph<T,L>::numedges(void)
{
    return (*vertices).countedges();
}

template<class T, class L> void ldigraph<T,L>::addedge(T origin, T destination, L label)
{
    (*vertices).addedge(origin, destination, label);
    return;
}

template<class T, class L> void ldigraph<T,L>::addvertex(T item)
{
    (*vertices).addvertex(item);
    return;
}

template<class T, class L> void ldigraph<T,L>::deleteedge(T origin, T destination)
{
    (*vertices).removeedge(origin, destination);
    return;
}

template<class T, class L> void ldigraph<T,L>::deletevertex(T item)
{
    (*vertices).remove(item);
    return;
}

template<class T, class L> edgelist<T,L> * ldigraph<T,L>::outgoingedges(T item)
{
    return (*vertices).outgoingedges(item);
}

template<class T, class L> void ldigraph<T,L>::prettyprint(void)
{
    cout << "\n\n====== Labelled Directed Graph ======\n\n";
    (*vertices).prettyprint();
    cout << "=================\n\n";
    return;
}
