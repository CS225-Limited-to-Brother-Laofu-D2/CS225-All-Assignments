//
//  lgraphtraversal.cpp
//  
//
//  Created by KD on 12.04.21.
//  Modified on 08.05.22.
//  Further modified to allow only double labels.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "lgraph.h"
#include "time.h"
using std::cout;
using std::cin;

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, i.e. the list of neighbour vertices. */
template<class T> vertex<T>::vertex(T item, vertex<T> *pt_next, vertex<T> *pt_prev)
{
    vertexid = item;
    next = pt_next;
    previous = pt_prev;
    edgelist = 0;
}

template<class T> int vertex<T>::numoutedges(void)
{
    if (edgelist != 0)
        return (*edgelist).getlength();
    return 0;
}

template<class T> T vertex<T>::getitem(void)
{
    return vertexid;
}

template<class T> vertex<T> * vertex<T>::getnext(void)
{
    return next;
}

template<class T> vertex<T> * vertex<T>::getprevious(void)
{
    return previous;
}

template<class T> elist<T> * vertex<T>::getedges(void)
{
    return edgelist;
}

template<class T> void vertex<T>::setitem(T item)
{
    vertexid = item;
    return;
}

template<class T> void vertex<T>::setnext(vertex<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void vertex<T>::setprevious(vertex<T> *pt_prev)
{
    previous = pt_prev;
    return;
}

template<class T> void vertex<T>::setedges(elist<T> *pt_edges)
{
    edgelist = pt_edges;
    return;
}

/* A vertexlist is a doubly linked list with vertices and a dummy node. */
template<class T> vertexlist<T>::vertexlist(void)
{
    dummy = new vertex<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numvertices = 0;
}

template<class T> int vertexlist<T>::getlength(void)
{
    return numvertices;
}

/* For counting edges we must add up the counts of outgoing edges for each vertex */
template<class T> int vertexlist<T>::countedges(void)
{
    int count = 0;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        count = count + (*pt).numoutedges();
        pt = (*pt).getnext();
    }
    return count;
}

template<class T> double vertexlist<T>::getlabel(T node, int index)
{
    vertex<T> * pt = (*dummy).getnext();
    elist<T> *edges;
    T node2;
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == node)
            edges = (*pt).getedges();
        if (i == index)
            node2 = (*pt).getitem();
        pt = (*pt).getnext();
    }
    if (edges != 0)
        return (*edges).getlabel(node2);
    return -1;
}

template<class T> T vertexlist<T>::getnode(int index)
{
    vertex<T> * pt = (*dummy).getnext();
    T node;
    for (int i = 0; i <= index; i++)
    {
        if (i == index)
            node = (*pt).getitem();
        pt = (*pt).getnext();
    }
    return node;
}

/* append is analogous to linked lists, i.e. we add a new vertex at the end and adjust pointers. */
template<class T> void vertexlist<T>::append(T item)
{
    vertex<T> * pt_last = (*dummy).getprevious();
    vertex<T> * pt_new = new vertex<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(dummy);
    (*pt_new).setprevious(pt_last);
    (*dummy).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++numvertices;
    return;
}

/* A new vertex is only added, if it is not yet in the list. */
template<class T> void vertexlist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

/* To check if a vertex is already in the list the list is scanned until the element is found. */
template<class T> bool vertexlist<T>::contains(T item)
{
    bool result = false;
    vertex<T> * pt = (*dummy).getnext();
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
template<class T> int vertexlist<T>::index(T item)
{
    int result = -1;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = i;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

/* In order to remove a vertex we have to find it in the list of vertices. If it has a non-empty list of neighbours, it cannot be deleted. It cannot be deleted, if it appears in any edgelist. */
template<class T> bool vertexlist<T>::remove(T item)
{
    bool result = false;
    vertex<T> * location = 0;
    vertex<T> *pt = (*dummy).getnext();
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
        elist<T> * edges = (*pt).getedges();
        if (edges != 0 && (*edges).contains(item) == true)
            /* if is appears in an edgelist, there is no delete. */
        {
            cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
            return result;
        }
        pt = (*pt).getnext();
    }
    /* Finally, we get to the deletion from the vertexlist. */
    if (location != 0)
    {
        result = true;
        vertex<T> * pt_prev = (*location).getprevious();
        vertex<T> * pt_next = (*location).getnext();
        (*pt_prev).setnext(pt_next);
        (*pt_next).setprevious(pt_prev);
        --numvertices;
    }
    /* The returned Boolean result indicates, if the vertex was deleted or not. */
    return result;
}

/* Adding an edge is done by first locating the origin vertex in the vertex list, then inserting the destination vertex into the associated edgelist. */
template<class T> void vertexlist<T>::addedge(T first, T second, double label)
{
    addvertex(second);
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).addvertex(second, label);
            else
            {
                elist<T> * newlist = new elist<T>(second, label);
                (*pt).setedges(newlist);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    /* If the origin vertex is not yet in the vertex list, it is first appended to the vertex list. The associated edgelist contains a single vertex. */
    append(first);
    pt = (*dummy).getprevious();
    elist<T> * newlist = new elist<T>(second, label);
    (*pt).setedges(newlist);
    return;
}

/* Removing an edge is done by first locating the origin vertex in the vertex list, then searching for the destination vertex into the associated edgelist. In this case the edge is always deleted, if it is found. */
template<class T> void vertexlist<T>::removeedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
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

template<class T> elist<T> * vertexlist<T>::edges(T node)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == node)
            return (*pt).getedges();
        pt = (*pt).getnext();
    }
    return 0;
}

/* To build list of outgoing edges for a given vertex, a new edge sequence is created for the output, then by scanning the associated edgelist edges (pairs of vertices) are added one by one. */
template<class T> edgelist<T> * vertexlist<T>::outgoingedges(T item)
{
    edgelist<T> * result = new edgelist<T>;
    vertex<T> * ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*ptv).getitem() == item)
        {
            elist<T> * edges = (*ptv).getedges();
            if (edges != 0)
                (*edges).addall(item, result);
            return result;
        }
        ptv = (*ptv).getnext();
    }
    return result;
}

/* only for testing */
template<class T> void vertexlist<T>::prettyprint(void)
{
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Edges with origin " << (*ptv).getitem() << " :\n";
        edgelist<T> * pte = outgoingedges((*ptv).getitem());
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }
    return;
}

/* The edge list for each vertex is organised analogous to the vertexlist, but the are no associated edgelists. The elements of the list are organised by the neighbour class. */
template<class T> neighbour<T>::neighbour(T item, double lab, neighbour<T> *pt_next, neighbour<T> *pt_prev)
{
    secondvertex = item;
    if (lab > 0)
        label = lab;
    else
        label = 1;
    next = pt_next;
    previous = pt_prev;
}

template<class T> T neighbour<T>::getitem(void)
{
    return secondvertex;
}

template<class T> double neighbour<T>::getlabel(void)
{
    return label;
}

template<class T> neighbour<T> * neighbour<T>::getnext(void)
{
    return next;
}

template<class T> neighbour<T> * neighbour<T>::getprevious(void)
{
    return previous;
}

template<class T> void neighbour<T>::setitem(T item)
{
    secondvertex = item;
    return;
}

template<class T> void neighbour<T>::setlabel(double lab)
{
    if (lab > 0)
        label = lab;
    else
        label = 1;
    return;
}

template<class T> void neighbour<T>::setnext(neighbour<T> * pt)
{
    next = pt;
    return;
}

template<class T> void neighbour<T>::setprevious(neighbour<T> * pt)
{
    previous = pt;
    return;
}

/* elist is the class used for the representation of doubly linked lists of vertices (no dummy node) associated with the vertices in the vertexlist. All functions are analogous to those defined for vertexlist. */
template<class T> elist<T>::elist(T item, double label)
{
    first = new neighbour<T>;
    (*first).setitem(item);
    length = 1;
    (*first).setlabel(label);
    (*first).setnext(first);
    (*first).setprevious(first);
}

template<class T> int elist<T>::getlength(void)
{
    return length;
}

template<class T> neighbour<T> * elist<T>::getfirst(void)
{
    return first;
}

template<class T> void elist<T>::append(T item, double label)
{
    neighbour<T> * pt_last = (*first).getprevious();
    neighbour<T> * pt_new = new neighbour<T>;
    (*pt_new).setitem(item);
    (*pt_new).setlabel(label);
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    return;
}

template<class T> void elist<T>::addvertex(T item, double label)
{
    if (contains(item) == false)
        append(item, label);
    return;
}

template<class T> bool elist<T>::contains(T item)
{
    bool result = false;
    neighbour<T> * pt = first;
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

template<class T> void elist<T>::remove(T item)
{
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            neighbour<T> * pt_prev = (*pt).getprevious();
            neighbour<T> * pt_next = (*pt).getnext();
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

template<class T> double elist<T>::getlabel(T item)
{
    neighbour<T> * neighb = first;
    for (int i = 0; i < length; i++)
    {
        if ((*neighb).getitem() == item)
            return (*neighb).getlabel();
        neighb = (*neighb).getnext();
    }
    return -1;
}

/* The function addall adds all pairs with the given item and the list members, i.e. all outgoing edges to the list given by the pointer pt. It exploit the function add on edgelists. */
template<class T> void elist<T>::addall(T item, edgelist<T> *pt)
{
    neighbour<T> * pte = first;
    for (int i = 0; i < length; i++)
    {
        (*pt).add(item, (*pte).getitem(), (*pte).getlabel());
        pte = (*pte).getnext();
    }
    return;
}

/* Edges are simply pairs of vertices with obvious get and set functions. */
template<class T> edge<T>::edge(T first, T second, double value)
{
    firstitem = first;
    seconditem = second;
    if (value > 0)
        label = value;
    else
        label = 1;
}

template<class T> T edge<T>::origin(void)
{
    return firstitem;
}

template<class T> T edge<T>::destination(void)
{
    return seconditem;
}

template<class T> double edge<T>::getlabel(void)
{
    return label;
}

template<class T> void edge<T>::setorigin(T item)
{
    firstitem = item;
    return;
}

template<class T> void edge<T>::setdestination(T item)
{
    seconditem = item;
    return;
}

template<class T> void edge<T>::setlabel(double value)
{
    if (value > 0)
        label = value;
    else
        label = 1;
    return;
}

/* only for testing */
template<class T> void edge<T>::prettyprint(void)
{
    cout << "(origin: " << origin() << ", destination: " << destination() << ", label: " << getlabel() << ")\n";
    return;
}

/* edgelists, i.e. sequences of pairs of vertices are only used for output purposes. */
template<class T> edgelist<T>::edgelist(void)
{
    reprarray = new edge<T>*[10000];
    numedges = 0;
}

template<class T> edge<T>* edgelist<T>::getedge(int index)
{
    return reprarray[index];
}

template<class T> int edgelist<T>::getnumedges(void)
{
    return numedges;
}

template<class T> void edgelist<T>::add(T item1, T item2, double label)
{
    edge<T> * newedge = new edge<T>(item1,item2,label);
    reprarray[numedges] = newedge;
    ++numedges;
    return;
}

template<class T> edgelist<T> *edgelist<T>::extend(edge<T> *extedge)
{
    edgelist<T> *newedgelist = new edgelist<T>();
    edge<T> *e;
    for (int i = 0; i < numedges; i++)
    {
        e = reprarray[i];
        (*newedgelist).add((*e).origin(), (*e).destination(), (*e).getlabel());
    }
    (*newedgelist).add((*extedge).origin(), (*extedge).destination(), (*extedge).getlabel());
    return newedgelist;
}

template<class T> void edgelist<T>::prettyprint(void)
{
    for (int i = 0; i < numedges; i++)
    {
        edge<T> * pte = reprarray[i];
        (*pte).prettyprint();
    }
    cout << "      --------\n";
    return;
}

/* Now define directed labelled graphs. A labelled digraph object just contains a pointer to a vertexlist. */
template<class T> ldigraph<T>::ldigraph(void)
{
    vertices = new vertexlist<T>;
}

template<class T> int ldigraph<T>::numvertices(void)
{
    return (*vertices).getlength();
}

template<class T> int ldigraph<T>::numedges(void)
{
    return (*vertices).countedges();
}

template<class T> void ldigraph<T>::addedge(T origin, T destination, double label)
{
    (*vertices).addedge(origin, destination, label);
    return;
}

template<class T> void ldigraph<T>::addvertex(T item)
{
    (*vertices).addvertex(item);
    return;
}

template<class T> void ldigraph<T>::deleteedge(T origin, T destination)
{
    (*vertices).removeedge(origin, destination);
    return;
}

template<class T> void ldigraph<T>::deletevertex(T item)
{
    (*vertices).remove(item);
    return;
}

template<class T> edgelist<T> * ldigraph<T>::outgoingedges(T item)
{
    return (*vertices).outgoingedges(item);
}

template<class T> int ldigraph<T>::index(T item)
{
    return (*vertices).index(item);
}

template<class T> double ldigraph<T>::getlabel(T node, int index)
{
    return (*vertices).getlabel(node, index);
}

template<class T> T ldigraph<T>::getnode(int index)
{
    return (*vertices).getnode(index);
}

template<class T> void ldigraph<T>::prettyprint(void)
{
    cout << "\n\n====== Labelled Directed Graph ======\n\n";
    (*vertices).prettyprint();
    cout << "=================\n\n";
    return;
}

template<class T> void ldigraph<T>::dijkstra(T startnode, edgelist<T> **paths, double *costs)
{
    int startindex = index(startnode);
    if (startindex < 0)
    {
        cout << "There is no vertex " << startnode << ".\n";
        return;
    }
    // initialisation
    int size = numvertices();
    costs = new double[size];
    paths = new edgelist<T>*[size];
    T nodes[size];
    bool processed[size];
    for (int i = 0; i < size; i++)
    {
        nodes[i] = getnode(i);
        paths[i] = new edgelist<T>;
        if (i == startindex)
        {
            processed[i] = true;
            costs[i] = 0;
        }
        else
        {
            processed[i] = false;
            costs[i] = getlabel(startnode, i);
            if (costs[i] > 0)
                (*paths[i]).add(startnode, nodes[i], costs[i]);
        }
    }
    double mincost, newcost, addcost;
    int minindex;
    T minnode;
    // iteration over all intermediate nodes
    for (int i = 0; i < size - 1; i++)
    {
        mincost = 0;
        for (int j = 0; j < size; j++)
        {
            if (!processed[j])
            {
                if (mincost == 0  && costs[j] > 0)
                {
                    mincost = costs[j];
                    minindex = j;
                }
                else
                {
                    if (costs[j] < mincost && 0 < costs[j])
                    {
                        mincost = costs[j];
                        minindex = j;
                    }
                }
            }
        }
        minnode = nodes[minindex];
        processed[minindex] = true;
        for (int k = 0; k < size; k++)
        {
            if (k != minindex)
            {
                addcost = getlabel(minnode, k);
                newcost = -1;
                if (costs[minindex] > 0 && addcost > 0)
                    newcost = costs[minindex] + addcost;
                if (newcost > 0 && (newcost < costs[k] || costs[k] < 0))
                {
                    edge<T> *extedge = new edge<T>(minnode, nodes[k], addcost);
                    costs[k] = newcost;
                    paths[k] = (*paths[minindex]).extend(extedge);
                }
            }
        }
    }
    // print the result
    cout << "Startnode: " << startnode << "\n";
    cout << "=======\n";
    for (int j = 0; j < size; j++)
    {
        if (j != startindex)
        {
            if (costs[j] == -1)
                cout << "The node " << nodes[j] << " is not reachable from the startnode " << startnode << "\n\n";
            else
            {
                
                cout << "Shortest path to node " << nodes[j] << ":\n";
                (*paths[j]).prettyprint();
                cout << "with path length: " << costs[j] << "\n";
                cout << "   -----\n\n";
            }
        }
    }
    return;
}
