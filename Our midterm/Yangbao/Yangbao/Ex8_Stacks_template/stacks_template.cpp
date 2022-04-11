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
    for (int i = 0; i < numitems1 + numitems2; ++i)
    {
        newarray[i] = reprarray[i];
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
    for (int i = 0; i < numitems1 + numitems2; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> T Stacks<T>::top1(void)
{
    // This function needs to be implemented
    int stack_length = this->getlength1();
    return this->reprarray[stack_length];
}

template<class T> T Stacks<T>::top2(void)
{
    // This function needs to be implemented
    int stack_length = this->getlength2();
    return this->reprarray[maxsize - stack_length];
}

template<class T> T Stacks<T>::pop1(void)
{
    // This function needs to be implemented
    int stack_length = this->getlength1();
    numitems1--;
    return this->reprarray[stack_length];
}

template<class T> T Stacks<T>::pop2(void)
{
    // This function needs to be implemented
    int stack_length = this->getlength2();
    numitems2--;
    return this->reprarray[maxsize - stack_length + 1];
}

template<class T> void Stacks<T>::push1(T item)
{
    // This function needs to be implemented
    if(maxsize == numitems1 + numitems2)
    {
        allocate();
    }
    int stack_length = this->getlength1();
    reprarray[stack_length + 1] = item;
    numitems1++;
}

template<class T> void Stacks<T>::push2(T item)
{
    // This function needs to be implemented
    if(maxsize == numitems1 + numitems2)
    {
        allocate();
    }
    int stack_length = this->getlength2();
    reprarray[maxsize - stack_length] = item;
    numitems2++;
}

template<class T> bool Stacks<T>::isempty1(void)
{
    // This function needs to be implemented
    if(numitems1 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T> bool Stacks<T>::isempty2(void)
{
    // This function needs to be implemented
    if(numitems2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T> void Stacks<T>::display(void)
{
    // This function needs to be implemented
    cout<<"In stack 1 we have (from top of the stack to the bottom of the stack)\n";
    for(int i = this->getlength1() ; i >= 1 ; i--)
    {
        cout<<reprarray[i]<<"\n";
    }
    cout<<"In stack 2 we have (from top of the stack to the bottom of the stack)\n";
    for(int i = maxsize - this->getlength2() + 1 ; i <= maxsize  ; i++)
    {
        cout<<reprarray[i]<<"\n";
    }
}
