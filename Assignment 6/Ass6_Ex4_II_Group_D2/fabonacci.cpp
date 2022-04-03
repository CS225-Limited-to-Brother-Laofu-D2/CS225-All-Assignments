//
//  fabonacci.cpp
//  Created by Group D2
//
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.h"
using std::cout;
using std::cin;
using std::hash;

/* This defines a constructor */
template<class K, class T> hashmap<K,T>::hashmap(int size)
{
    maxsize = size;
    if (size < 20000)
        maxsize = 20000; // default size is 20; no smaller hashmaps are considered
    numitems = 0; // initially, the hashmap is empty
    keyarray = new K*[maxsize];  // allocate space for the array of pointers
    reprarray = new T[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        keyarray[i] = 0;
    }
    K *pt0 = new K;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}

template<class K, class T> T & hashmap<K,T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (keyarray[index - 1] != 0 && keyarray[index - 1] != pt_nil)
        return reprarray[index - 1];
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class K, class T> T hashmap<K,T>::fabonacci(int order)
{
    hash<int> hashfunction;  //the keyarray and reprarray are used for Memoisation
    int index;
    index = hashfunction(order) % maxsize;
    if(keyarray[index]!=0) //if alredy in look-up table, just return the number
    {
        return reprarray[index];
    }
    cout<<"This time we didn't use memorization\n";
    //if not in the look-up table, calculate the number and store it in.
    if(order==0){
        reprarray[index]=0;
        K *loc=new K;
        *loc=order;
        keyarray[index]=loc;
    }else if(order==1 || order==2){
        reprarray[index]=1;
        K *loc=new K;
        *loc=order;
        keyarray[index]=loc;
    }else{
        reprarray[index]=fabonacci(order-2)+fabonacci(order-1);
        K* loc=new K;
        *loc = order;
        keyarray[index]=loc;
    }
    ++ numitems;
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return reprarray[index];
}

template<class K, class T> void hashmap<K,T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    K **newkeyarray = new K*[newsize];
    T *newarray = new T[newsize];
    // allocate space for a new hashmap of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newkeyarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (keyarray[i] != 0 && keyarray[i] != pt_nil)
        {
            K item = *keyarray[i];
            T value = reprarray[i];
            hash<K> hashfunction;       
            int index = hashfunction(item) % newsize;
                // recompute the new hash value
            while (newkeyarray[index] != 0)  // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newkeyarray[index] = keyarray[i];  // do the actual copying
            newarray[index] = reprarray[i];  // do the actual copying
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    keyarray = newkeyarray;   // make the new hashmap
    reprarray = newarray;
    maxsize = newsize;   // update the size
}