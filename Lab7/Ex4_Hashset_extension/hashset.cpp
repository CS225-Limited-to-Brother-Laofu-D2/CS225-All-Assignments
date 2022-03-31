//
//  hashset.cpp
//  
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashset.h"
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::hash;

/* This defines a constructor */
template<class T> hashset<T>::hashset(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new T*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
    }
    T *pt0 = new T;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
    
    p=499;
    a =111;
    b =222;
    m = maxsize;
}

// template<class T> hashset<T>::~hashset(void)
// {
//     delete[] reprarray;
// }

template<class T> T & hashset<T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (reprarray[index - 1] != 0 && reprarray[index - 1] != pt_nil)
        return *reprarray[index - 1];
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class T> void hashset<T>::add(T item)
{
    // hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hash(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return;   // item found; no insertion
        if (location < 0 && reprarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        index = (index + 1) % maxsize;
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    T *pt = new T;
    *pt = item;
    reprarray[location] = pt;   // store item in the hashtable
    ++ numitems;
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        // std::cout<<numitems << ' ' << maxsize<<std::endl;
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return;
}

template<class T> void hashset<T>::remove(T item)
{
    // hash<T> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hash(item) % maxsize;
    while (reprarray[index] != 0)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
                    // item found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (reprarray[nextindex] == 0)
                reprarray[index] = 0;
            else
                reprarray[index] = pt_nil;
            --numitems;
            int load = 100 * numitems / maxsize;
            if (load <= 25)
                // if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
            {
                int newsize = numitems;
                if (newsize < 20)
                    newsize = 20;
                rehash(newsize);
            }
            return;
        }
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}

template<class T> bool hashset<T>::member(T item)
{
    int index;
    index = hash(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so item is not in the hashtable
}

template<class T> void hashset<T>::rehash(int newsize)
{
    /*
        You should modify this function
        hint: you can use rand() to generate a random number between 0 and RAND_MAX
    */
    // std::cout<<newsize<<std::endl;
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    //update a,b,m

    int a =rand() % this->p;
    int b =rand() % this->p;
    int m = newsize;
    update(a,b,m);

    T **newarray = new T*[newsize];   // allocate space for a new hashtable of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (reprarray[i] != 0 && reprarray[i] != pt_nil)
        {
            T item = *reprarray[i];
            int index = hash(item) % newsize;
                // recompute the new hash value
            while (newarray[index] != 0)  // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newarray[index] = reprarray[i];  // do the actual copying
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    reprarray = newarray;   // make the new hashtable the one of the hashset object
    maxsize = newsize;   // update the size
}

template<class T> void hashset<T>::display(void) // only for test purposes
{
    // cout << "The size of the hashtable is: " << maxsize << "\n";
    // cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "None ";
        else if (reprarray[i] == pt_nil)
            cout << "free ";
        else
            cout << *reprarray[i]<< ' ';
    }
    cout<<' '<<std::endl;
    return;
}

template<class T> int hashset<T>::get_num(void)
{
    return maxsize;
}
template<class T> void hashset<T>::update(int a, int b, int m)
{
    /*
    Input:
        a,b,m: the new parameter, you should update the corresponding parameters
        in the hashset class.
    Output:
        None
    */
    this->a = a;
    this->b = b;
    this->m = m;
}

template<class T> int hashset<T>::hash(T value)
{
    /*
    Input: 
        value: the original value
    Output:
        A hash value 
    */
    return (int(a * value + b) % p) % m;
}



int main()
{
    std::vector<int> temp;
    for (int i = 0; i< 100; i++){
        temp.push_back(i);
    }
    srand(1234);
    std::random_shuffle(temp.begin(),temp.end());
    std::cout<<"Here is test case 1:"<<std::endl;
    hashset<int> myhashtable1(20);
    int size = 15;
    std::cout<<"The num of item is: "<< size << std::endl;
    for (int i = 0; i< size; i++)
    {
        myhashtable1.add(temp[i]);
    }
    std::cout << "The number of elements in the hashtable is: " << myhashtable1.get_num() <<std::endl;
    std::cout<<"Correct hash table is: "<<std::endl;
    std::cout<<"None None 92 None 44 None 97 None 75 62 None None None 43 45 8 None 48 99 None 64 None 29 None 69 None 34 None 25 None "<<std::endl;
    std::cout<<"Your hash table is:" <<std::endl; 
    myhashtable1.display();
    
    std::cout<<'\n'<<std::endl;
    std::cout<<"Here is test case 2:"<<std::endl;
    hashset<int> myhashtable2(20);
    size = 25;
    std::cout<<"The num of item is: "<< size << std::endl;
    for (int i = 0; i< size; i++)
    {
        myhashtable2.add(temp[i]);
    }
    std::cout << "The number of elements in the hashtable is: " << myhashtable2.get_num() <<std::endl;
    std::cout<<"Correct hash table is: "<<std::endl;
    std::cout<<"67 34 None None 32 None None None None 25 98 44 77 None None None None None 68 None 75 14 21 None None None None 99 None 45 12 64 92 None None None 69 97 57 43 None 62 41 8 48 29 "<<std::endl;
    std::cout<<"Your hash table is:" <<std::endl; 
    myhashtable2.display();

    return 0;
}



