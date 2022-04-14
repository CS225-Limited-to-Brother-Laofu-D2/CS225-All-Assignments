//
//  trie.cpp
//  
//
//  Created by KD on 20.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

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

/* the constructor creates a node with the given value and next and follow pointers */
template<class T> trienode<T>::trienode(T item, bool l, trienode<T> *pt_next, trienode<T> *pt_follow)
{
    data = item;
    last = l;
    next = pt_next;
    follow = pt_follow;
}

/* the get operations */
template<class T> T trienode<T>::getdata(void)
{
    return data;
}

template<class T> bool trienode<T>::getlast(void)
{
    return last;
}

template<class T> trienode<T> *trienode<T>::getnext(void)
{
    return next;
}

template<class T> trienode<T> *trienode<T>::getfollow(void)
{
    return follow;
}

/* the set operations */
template<class T> void trienode<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void trienode<T>::setlast(bool l)
{
    last = l;
    return;
}

template<class T> void trienode<T>::setnext(trienode<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void trienode<T>::setfollow(trienode<T> *pt_follow)
{
    follow = pt_follow;
    return;
}

/* the constructor creates an empty trie containing just a null pointer at the start */
template<class T> trie<T>::trie(void)
{
    start = 0;
}

/* the insert and intrie functions are realised recursively starting from the start using the corresponding auxiliary functions */
template<class T> void trie<T>::insert(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    start = _insert(start, newlist);
    return;
}

template<class T> bool trie<T>::intrie(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    return contains(start, newlist);
}
/* auxiliary function for insertion */
template<class T> trienode<T> *trie<T>::_insert(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0)
        return 0;
    T key = list[1];  // take the first element of the new list
    if (pt == 0)  // case of null pointer: create a new trienode
    {
        list.remove(1);
        trienode<T> *newnode = new trienode<T>;
        (*newnode).setdata(key);  // set the value of the new trienode
        /* mark the trienode as final, if the inout list is used up */
        if (list.getlength() == 0)
            (*newnode).setlast(true);
        /* recursively proceed with the next element of the input list */
        (*newnode).setfollow(_insert((*newnode).getfollow(), list));
        return newnode;
    }
    if ((*pt).getdata() == key) // case of a prefix already in the trie
    {
        list.remove(1);
        if (list.getlength() == 0)
        {
            (*pt).setlast(true);
            return pt;
        }
        /* just skip over the prefix */
        (*pt).setfollow(_insert((*pt).getfollow(), list));
    }
    else
        /* otherwise follow the next pointer */
        (*pt).setnext(_insert((*pt).getnext(), list));
    return pt;
}

template<class T> bool trie<T>::contains(trienode<T> *pt, AList<T> list)
{
    // This function needs to be implemented
    if(pt == nullptr)
    {
        return false;
    }
    T key = list.getitem(1);
    if(list.getlength() == 1 && key == pt->data && pt->getlast() == true)
    {
        return true; // Found only if it matches and at the same time this is the last of the word
    }
    if(list.getlength() != 1 && key == pt->getdata())
    {
        list.remove(1);
        return contains(pt->getfollow(),list);
    }
    if(key != pt->getdata())
    {
        return contains(pt->getnext(),list);
    }
    else
    {
        return false;
    }
}

template<class T> void trie<T>::display(void)
{
    AList<T> list;
    _display(start, list);
    cout << "\n";
}

template<class T> void trie<T>::_display(trienode<T> * pt, AList<T> list)
{
    if (pt != 0)
    {
        list.append((*pt).getdata());
        if ((*pt).getlast() == true)
        {
            cout << "Trie entry: ";
            for (int i = 1; i <= list.getlength(); i++)
            {
                cout << list[i];
                if (i != list.getlength())
                    cout << " , ";
                else
                    cout << "\n";
            }
            if ((*pt).getfollow() != 0)
                _display((*pt).getfollow(),list);
        }
        else
            _display((*pt).getfollow(), list);
        list.remove(list.getlength());
        if ((*pt).getnext() != 0)
            _display((*pt).getnext(), list);
    }
    return;
}

template<class T> void trie<T>::correct1(AList<T> list)
{
    /* This function needs to be implemented. It should try to find the input word in the TRIE. If unsussessful, it should output words from the dictionary that extend the given word (not found in the dictionary) by one symbol. */
    if(intrie(list) == true)
    {
        cout<<"This word is already in the dictionary."<<"\n";
    }
    else
    {   
        AList<T> temp;
        for(int i = 1 ; i <= list.getlength() ; i++)
        {
            temp.append(list.getitem(i));
        }
        trienode<T> *pt = start;
        while(pt != nullptr) // We need to find whether there's a one symbol extension.
        {
            T key = list.getitem(1);
            if(list.getlength() == 1 && key == pt->data)
            {
                // In this case we need to decide whether it is exacly one symbol.
                if(pt->getfollow()->getlast() == true)
                {
                    cout<<"A possible extension word (extended by one symbol) is ";
                    for(int i = 1 ; i <= temp.getlength() ; i++)
                    {
                        cout<<temp.getitem(i);
                    }
                    cout<<pt->getfollow()->data<<"\n";
                    pt = pt->getfollow();
                    while(pt->getnext() != nullptr)
                    {
                        if(pt->getnext()->getlast() == true)
                        {
                           cout<<"A possible extension word (extended by one symbol) is ";
                            for(int i = 1 ; i <= temp.getlength() ; i++)
                            {
                                cout<<temp.getitem(i);
                            }
                            cout<<pt->getnext()->data<<"\n"; 
                        }
                        pt = pt->getnext();
                    }
                    return;
                }
            }
            if(pt->data != key)
            {
                pt = pt->getnext();
                continue;
            }
            if(pt->data == key)
            {
                list.remove(1);
                pt = pt->getfollow();
                continue;
            }
        }
        cout<<"No such word from the dictionary that extend the given word (not found in the dictionary) by one symbol.\n";
    }
}

template<class T> void trie<T>::correct2(AList<T> list)
{
    /* This function needs to be implemented. It should try to find the input word in the TRIE. If unsussessful, it should output words from the dictionary that are prefixes of the given word (not found in the dictionary) with one or two symbols less. */
    if(intrie(list) == true)
    {
        cout<<"This word is already in the dictionary."<<"\n";
    }
    else
    {
        AList<T> temp;
        for(int i = 1 ; i <= list.getlength() ; i++)
        {
            temp.append(list.getitem(i));
        }
        trienode<T> *pt = start;
        trienode<T> *previous = new trienode<T>;
        while(pt != nullptr) // We need to find whether there's a one symbol extension.
        {
            T key = list.getitem(1);
            if(pt->data != key)
            {
                if(list.getlength() == 1 || list.getlength() == 2)
                {
                    break;
                }
                previous = pt;
                pt = pt->getnext();
                continue;
            }
            if(pt->data == key)
            {
                list.remove(1);
                previous = pt;
                if(pt->getfollow() == nullptr || ((list.getlength() == 1 || list.getlength() == 2) && pt->getfollow()->getlast() == false))
                {
                    break;
                }
                pt = pt->getfollow();
                continue;
            }
        }
        if(list.getlength() == 1)
        {
            if(previous->getlast() == true) // Which means two symbols' prefix
            {
                cout<<"A possible prefix word (shorten by two symbols) is ";
                for(int i = 1 ; i <= temp.getlength() - 2 ; i++)
                {
                    cout<<temp.getitem(i);
                }
                cout<<"\n";
            }
            if(pt->getlast() == true) // Which means one symbols' prefix
            {
                cout<<"A possible prefix word (shorten by one symbols) is ";
                for(int i = 1 ; i <= temp.getlength() - 1 ; i++)
                {
                    cout<<temp.getitem(i);
                }
                cout<<"\n";
            }
            return;
        }
        if(list.getlength() == 2) // In this case we only have one symbol prefix.
        {
            if(pt->getlast() == true) // Which means one symbols' prefix
            {
                cout<<"A possible prefix word (shorten by one symbols) is ";
                for(int i = 1 ; i <= temp.getlength() - 2 ; i++)
                {
                    cout<<temp.getitem(i);
                }
                cout<<"\n";
            }
            return;
        }
        cout<<"No such word from the dictionary that that are prefixes of the given word (not found in the dictionary) with one or two symbols less.\n";
    }
}

template<class T> void trie<T>::correct3(AList<T> list)
{
    /* This function needs to be implemented. It should try to find the input word in the TRIE. If unsussessful, it should output words from the dictionary that differ from the given word (not found in the dictionary) by exactly one symbol. */
    if(intrie(list) == true)
    {
        cout<<"This word is already in the dictionary."<<"\n";
    }
    else
    {   
        cout<<"Prefix or one symbol extension difference is not considered, please use correct1 and correct2 function for that.\n";
        // Compare every possible 1 symbol dif in this dictionary.
        int length = list.getlength();
        bool found = false;
        for(int i = 1 ; i <= length ; i++)
        {
            T temp = list.getitem(i);
            T symbol = 'a';
            for(int k = 0 ; k <= 25 ; k++)
            {
                T p = symbol + k;
                //cout<<p<<"\n";
                list.setitem(i,p); // search from a to Z.p, for example, we want find "word", then we first search from "aord" to "Zord"
                if(intrie(list) == true)
                {
                    found = true;
                    cout<<"A possible one difference word is ";
                    for(int counter = 1; counter <= list.getlength() ; counter++)
                    {
                        cout<<list.getitem(counter);
                    }
                    cout<<"\n";
                }
                if(k == 25)
                {
                    k = -1;
                    if(symbol == 'A')
                    {
                        break;
                    }
                    symbol = 'A';
                }
            }
            symbol = 'a';
            list.setitem(i,temp); // Restore it. say, back to "word"
        }
        if(found == true)
        {
            return;
        }
        else
        {
           cout<<"No such word from the dictionary that differ from the given word (not found in the dictionary) by exactly one symbol.\n"; 
        }
    }
}
