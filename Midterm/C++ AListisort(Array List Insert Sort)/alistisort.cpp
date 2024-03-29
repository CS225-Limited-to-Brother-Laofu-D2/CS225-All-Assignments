//
//  alistsort.cpp
//  
//
//  Created by KD on 22.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alistisort.h"
using std::cout;
using std::cin;

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

template<class T> int AList<T>::find_min(int limit)
{
    // We assume that the list is not empty.
    T value = reprarray[0]; // value is to store the minimal list entry
    int index = 0; // index is to store the position of the minimal value
    for (int i = 1; i < limit; i++) // scan the whole list
    {
        if (reprarray[i] < value)
        {
            value = reprarray[i]; // update value, when a smaller entry is found
            index = i; // update the index accordingly
        }
    }
    return index;
}

template<class T> void AList<T>::isort(void)
{
    if (numitems > 1)
        // sorting only makes sense for lists with at least 2 elements
    {
        T * newarray = new T[maxsize]; // create a new list of the same size
        int index;
        int num = numitems;
        for (int i = 0; i < num; i++)
        {
            index = find_min(numitems);
            // find the position with the minimum value
            newarray[i] = reprarray[index]; // add the found value to the outlist
            remove(index + 1); // delete the minimum value
        }
        delete reprarray;
        reprarray = newarray; // store the outlist as the new list
        numitems = num;
    }
    return;
}

template<class T> void AList<T>::isort_ip(void)
{
    if (numitems > 1)
        // sorting only makes sense for lists with at least 2 elements
    {
        int index;
        int num = numitems;
        for (int i = 0; i < num; i++)
        {
            index = find_min(num - i);
            // find the position with the minimum value among the first numitems - i list values
            append(reprarray[index]); // append the found minimum at the end
            remove(index + 1); // delete the minimum value
        }
    }
    return;
}
