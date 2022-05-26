//
//  lgraph.h
//  
//
//  Created by KD on 12.04.21.
//  Modified on 08.05.22 -- Adding labels to edges
//  Further modified to positive real numbers as labels
//

#ifndef lgraph_h
#define lgraph_h

template<class T> class vertexlist;

template<class T> class edgelist;

template<class T> class edge;

template<class T> class elist;

template<class T> class vertex
{
    friend class vertexlist<T>;
public:
    vertex(T item = 0, vertex<T> *pt_next = 0, vertex<T> *pt_prev = 0);
    int numoutedges(void);
    T getitem(void);
    vertex<T> * getnext(void);
    vertex<T> * getprevious(void);
    elist<T> * getedges(void);
    void setitem(T item);
    void setnext(vertex<T> * pt_next);
    void setprevious(vertex<T> * pt_prev);
    void setedges(elist<T> * pt_edges);
private:
    T vertexid;
    vertex<T> * next;
    vertex<T> * previous;
    elist<T> * edgelist;
};

template<class T> class vertexlist
{
public:
    vertexlist(void);
    int getlength(void);
    int countedges(void);
    double getlabel(T node, int index);
    T getnode(int index);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    int index(T item);
    bool remove(T item);
    void addedge(T first, T second, double label);
    void removeedge(T first, T second);
    elist<T> * edges(T node);
    edgelist<T> * outgoingedges(T item);
    void prettyprint(void); // only for testing
private:
    vertex<T> * dummy;
    int numvertices;
};

template<class T> class neighbour
{
    friend class elist<T>;
public:
    neighbour(T item = 0, double lab = 0, neighbour<T> * pt_next = 0, neighbour<T> * pt_prev = 0);
    T getitem(void);
    double getlabel(void);
    neighbour<T> * getnext(void);
    neighbour<T> * getprevious(void);
    void setitem(T item);
    void setlabel(double lab);
    void setnext(neighbour<T> * pt);
    void setprevious(neighbour<T> * pt);
private:
    T secondvertex;
    double label;
    neighbour<T> * next;
    neighbour<T> * previous;
};

template<class T> class elist
{
public:
    elist(T item, double label);
    int getlength(void);
    neighbour<T> * getfirst(void);
    void append(T item, double label);
    void addvertex(T item, double label);
    bool contains(T item);
    void remove(T item);
    double getlabel(T item);
    void addall(T item, edgelist<T> * pt);
private:
    neighbour<T> * first;
    int length;
};

template<class T> class edge
{
    friend class edgelist<T>;
public:
    edge(T first, T second, double value);
    T origin(void);
    T destination(void);
    double getlabel(void);
    void setorigin(T item);
    void setdestination(T item);
    void setlabel(double value);
    void prettyprint(void); // only for testing
private:
    T firstitem;
    T seconditem;
    double label;
};

template<class T> class edgelist
{
public:
    edgelist(void);
    edge<T> * getedge(int index);
    int getnumedges(void);
    void add(T item1, T item2, double label);
    edgelist<T> * extend(edge<T> *extedge);
    void prettyprint(void); // only for testing
private:
    edge<T> ** reprarray;
    int numedges;
};

template<class T> class ldigraph
{
public:
    ldigraph(void);
    int numvertices(void);
    int numedges(void);
    void addedge(T origin, T destination, double label);
    void addvertex(T item);
    void deleteedge(T origin, T destination);
    void deletevertex(T item);
    edgelist<T> * outgoingedges(T item);
    int index(T item);
    double getlabel(T node, int index);
    T getnode(int index);
    void prettyprint(void); // only for testing
    void dijkstra(T startnode, edgelist<T> **paths, double *costs);
protected:
    vertexlist<T> * vertices;
};

#endif /* lgraph_h */
