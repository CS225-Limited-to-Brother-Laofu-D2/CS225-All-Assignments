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
    for(int i=0;i<numitems2;i++){
        newarray[newsize-1-i]=reprarray[maxsize-1-i];
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
    for(int i=0;i<numitems2;i++){
        newarray[newsize-1-i]=reprarray[newsize-1-i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> T Stacks<T>::top1(void)
{
    // This function needs to be implemented
    int temp=numitems1-1;
    return reprarray[temp];
}

template<class T> T Stacks<T>::top2(void)
{
    // This function needs to be implemented
    int temp=maxsize-numitems2;
    return reprarray[temp];
}

template<class T> T Stacks<T>::pop1(void)
{
    // This function needs to be implemented
    if(isempty2()){
        cout << "The stack is empty, can NOT pop!\n";
        exit(EXIT_FAILURE);
    }else if(numitems2+numitems1<=maxsize/4){
        deallocate();
        int temp=numitems1-1;
        numitems1--;
        return reprarray[temp];
    }else{
        int temp=numitems1-1;
        numitems1--;
        return reprarray[temp];
    }
}

template<class T> T Stacks<T>::pop2(void)
{
    // This function needs to be implemented
    if(isempty2()){
        cout << "The stack is empty, can NOT pop!\n";
        exit(EXIT_FAILURE);
    }else if(numitems2+numitems1<=maxsize/4){
        deallocate();
        int temp=maxsize-numitems2;
        numitems2--;
        return reprarray[temp];
    }else{
        int temp=maxsize-numitems2;
        numitems2--;
        return reprarray[temp];
    }
}

template<class T> void Stacks<T>::push1(T item)
{
    // This function needs to be implemented
    if(numitems1+numitems2==maxsize){
        allocate();
    }
    reprarray[numitems1]=item;
    numitems1++;
}

template<class T> void Stacks<T>::push2(T item)
{
    // This function needs to be implemented
    if(numitems1+numitems2==maxsize){
        allocate();
    }
    reprarray[maxsize-numitems2-1]=item;
    numitems2++;
}

template<class T> bool Stacks<T>::isempty1(void)
{
    // This function needs to be implemented
    bool result;
    result=false;
    if(numitems1==0)
        result=true;
    return result;
}

template<class T> bool Stacks<T>::isempty2(void)
{
    // This function needs to be implemented
    bool result;
    result=false;
    if(numitems2==0)
        result=true;
    return result;
}

template<class T> void Stacks<T>::display(void)
{
    // This function needs to be implemented
    cout<<"The items in the stack 1 are follows:\n";
    cout<<"output the element first entering the stack first \n";
    for(int i=0;i<numitems1;i++){
        cout<<reprarray[i]<<"\n";
    }
    cout<<"The items in the stack 2 are follows:\n";
    cout<<"output the element first entering the stack first \n";
    for(int i=0;i<numitems2;i++){
        cout<<reprarray[maxsize-1-i]<<"\n";
    }
}
