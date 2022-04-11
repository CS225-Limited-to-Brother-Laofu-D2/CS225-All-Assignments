//
//  stacks.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 04.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "stacks.h"
using std::cout;
using std::cin;

template<class T> T &Stacks<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int Stacks<T>::getlength1(void)
{
    return numitems1;
}

template<class T> int Stacks<T>::getlength2(void)
{
    return numitems2;
}

/*
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
} */

template<class T> void Stacks<T>::allocate(void)
{
    // This function needs to be modified
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems1; ++i)
    {
        newarray[i] = reprarray[i];
    }
    for (int i = maxsize - numitems2; i < maxsize; i++)
    {
        newarray[i + maxsize] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

/*
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
} */

template<class T> void Stacks<T>::deallocate(void)
{
    // This function needs to be modified
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems1; ++i)
    {
        newarray[i] = reprarray[i];
    }
    for (int i = maxsize - numitems2; i < maxsize; i++)
    {
        newarray[i] = reprarray[i + maxsize];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> T Stacks<T>::top1(void)
{
    // This function needs to be implemented
    if (numitems1 > 0)
        return reprarray[numitems1 - 1];
    else
    {
        cout << "The stack1 is empty.";
        exit(EXIT_FAILURE);
    }
}

template<class T> T Stacks<T>::top2(void)
{
    // This function needs to be implemented
    if (numitems2 > 0)
        return reprarray[maxsize - numitems2];
    else
    {
        cout << "The stack2 is empty.";
        exit(EXIT_FAILURE);
    }
}

template<class T> T Stacks<T>::pop1(void)
{
    // This function needs to be implemented
    if (numitems1 > 0)
    {
        T result = reprarray[numitems1 - 1];
        if ((numitems1 + numitems2 <= maxsize / 4) && (maxsize > minsize))
            deallocate();
        --numitems1;
        return result;
    }
    else
    {
        cout << "The stack1 is empty.";
        exit(EXIT_FAILURE);
    }
}

template<class T> T Stacks<T>::pop2(void)
{
    // This function needs to be implemented
    if (numitems1 > 0)
    {
        T result = reprarray[maxsize - numitems2];
        if ((numitems1 + numitems2 <= maxsize / 4) && (maxsize > minsize))
            deallocate();
        --numitems2;
        return result;
    }
    else
    {
        cout << "The stack2 is empty.";
        exit(EXIT_FAILURE);
    }
}

template<class T> void Stacks<T>::push1(T item)
{
    // This function needs to be implemented
    if (numitems1 + numitems2 == maxsize)
        allocate();
    reprarray[numitems1] = item;
    ++numitems1;
    return;
}

template<class T> void Stacks<T>::push2(T item)
{
    // This function needs to be implemented
    if (numitems1 + numitems2 == maxsize)
        allocate();
    reprarray[maxsize - numitems2 -1] = item;
    ++numitems2;
    return;
}

template<class T> bool Stacks<T>::isempty1(void)
{
    // This function needs to be implemented
    if (numitems1 > 0)
        return false;
    else
        return true;
}

template<class T> bool Stacks<T>::isempty2(void)
{
    // This function needs to be implemented
    if (numitems2 > 0)
        return false;
    else
        return true;
}

template<class T> void Stacks<T>::display(void)
{
    // This function needs to be implemented
    cout << "The stack elements from top to bottom are:\n";
    for (int i = numitems1; i > 0; --i)
    {
        cout << reprarray[i-1] <<"\n";
    }
    for (int i = numitems2; i < maxsize; i++)
    {
        cout << reprarray[i-1] <<"\n";
    }
    
}
