//
//  lgraph.h
//  
//
//  Created by KD on 12.04.21.
//  Modified on 08.05.22 -- Adding labels to edges
//

#ifndef lgraph_h
#define lgraph_h

template<class T> class fifo
{
public:
    fifo(int size = 10);
//    virtual ~fifo();
    T &operator[](int index);
    int getlength(void);
    bool isempty(void);
    T back(void);
    T front(void);
    void pushback(T value);
    T popfront(void);
private:
    int maxsize, minsize;
    int first, last;
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

template<class T> class AList
{
public:
    AList(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(AList<T> &list);
    bool member(T value);
    bool equal(AList<T> &list);
    bool sublist(AList<T> &list);
protected:
    int numitems;
    T *reprarray;
private:
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T> class AListsort : public AList<T>
{
public:
    AListsort(int size = 20) : AList<T>(size){};
    void bsort(void);
    void qsort(int thr);
};

template<class T, class L> class vertexlist;

template<class T, class L> class edgelist;

template<class T, class L> class edge;

template<class T, class L> class elist;

template<class T, class L> class vertex
{
    friend class vertexlist<T,L>;
public:
    vertex(T item = 0, vertex<T,L> *pt_next = 0, vertex<T,L> *pt_prev = 0);
    int numoutedges(void);
    T getitem(void);
    vertex<T,L> * getnext(void);
    vertex<T,L> * getprevious(void);
    elist<T,L> * getedges(void);
    void setitem(T item);
    void setnext(vertex<T,L> * pt_next);
    void setprevious(vertex<T,L> * pt_prev);
    void setedges(elist<T,L> * pt_edges);
private:
    T vertexid;
    vertex<T,L> * next;
    vertex<T,L> * previous;
    elist<T,L> * edgelist;
};

template<class T, class L> class vertexlist
{
public:
    vertexlist(void);
    int getlength(void);
    int countedges(void);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    bool remove(T item);
    void addedge(T first, T second, L label);
    void removeedge(T first, T second);
    elist<T,L> * edges(T node);
    edgelist<T,L> * outgoingedges(T item);
    void prettyprint(void); // only for testing
private:
    vertex<T,L> * dummy;
    int numvertices;
};

template<class T, class L> class neighbour
{
    friend class elist<T,L>;
public:
    neighbour(T item = 0, L lab = 0, neighbour<T,L> * pt_next = 0, neighbour<T,L> * pt_prev = 0);
    T getitem(void);
    L getlabel(void);
    neighbour<T,L> * getnext(void);
    neighbour<T,L> * getprevious(void);
    void setitem(T item);
    void setlabel(L lab);
    void setnext(neighbour<T,L> * pt);
    void setprevious(neighbour<T,L> * pt);
private:
    T secondvertex;
    L label;
    neighbour<T,L> * next;
    neighbour<T,L> * previous;
};

template<class T, class L> class elist
{
public:
    elist(T item, L label);
    int getlength(void);
    neighbour<T,L> * getfirst(void);
    void append(T item, L label);
    void addvertex(T item, L label);
    bool contains(T item);
    void remove(T item);
    void addall(T item, edgelist<T,L> * pt);
private:
    neighbour<T,L> * first;
    int length;
};

template<class T, class L> class edge
{
    friend class edgelist<T,L>;
public:
    edge(T first, T second, L value);
    T origin(void);
    T destination(void);
    L getlabel(void);
    void setorigin(T item);
    void setdestination(T item);
    void setlabel(L value);
    void prettyprint(void); // only for testing
private:
    T firstitem;
    T seconditem;
    L label;
};

template<class T, class L> class edgelist
{
public:
    edgelist(void);
    int getnumedges(void);
    void add(T item1, T item2, L label);
    void prettyprint(void); // only for testing
private:
    edge<T,L> ** reprarray;
    int numedges;
};

template<class T, class L> class ldigraph
{
public:
    ldigraph(void);
    int numvertices(void);
    int numedges(void);
    void addedge(T origin, T destination, L label);
    void addvertex(T item);
    void deleteedge(T origin, T destination);
    void deletevertex(T item);
    edgelist<T,L> * outgoingedges(T item);
    void prettyprint(void); // only for testing
protected:
    vertexlist<T,L> * vertices;
};

#endif /* lgraph_h */
