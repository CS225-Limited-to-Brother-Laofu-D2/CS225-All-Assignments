//
//  alistq.h
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 22.01.21
//

#ifndef alistq_h
#define alistq_h

template<class T> class AList
{
public:
    AList(int size = 20);
//    virtual ~AList();
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
//    virtual ~AListsort();
    void bsort(void);
    void qsort(int thr);
};

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

//template<class T> AList<T>::~AList()
//{
//    delete[] reprarray;
//}

//template<class T> AList<T>::~AList()
//{
//    delete[] reprarray;
//}

#endif /* alistq_h */
