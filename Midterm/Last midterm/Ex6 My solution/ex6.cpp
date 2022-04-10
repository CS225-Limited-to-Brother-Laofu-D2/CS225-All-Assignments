
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "ex6.h"
using std::cout;
using std::cin;
using std::endl;

template<class T> fifo<T>::fifo(int size)
{
    maxsize = size;
    if (size < 10)
        minsize = size;
    else
        minsize = 10;
    numitems = 0;
    first = 0;
    last = -1;
    reprarray = new pair<T>[maxsize];
}

template<class T> fifo<T>::~fifo()
{
   delete[] reprarray;
}

template<class T> pair<T> &fifo<T>::operator[](int index)
{
    if ((1 <= index) && (index <= numitems))
    {
        int relindex = (index + first -1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "Error: index " << index << " out of range.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> int fifo<T>::getlength(void)
{
    return numitems;
}

template<class T> bool fifo<T>::isempty(void)
{
    if (numitems == 0)
        return true;
    else
        return false;
}

template<class T> pair<T> fifo<T>::front(void)
{
    if (isempty() == false)
        return reprarray[first];
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> pair<T> fifo<T>::back(void)
{
    if (isempty() == false)
    {
        int relindex = (first + numitems - 1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::pushback(pair<T> value)
{
    if (numitems == maxsize)
        allocate();
    last = last + 1;
    last = last % maxsize;
    // last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

template<class T> pair<T> fifo<T>::popfront(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false)
    {
        pair<T> frontelement = reprarray[first];
        first = first + 1;
        first = first % maxsize;
        // first = ++first % maxsize;
        --numitems;
        return frontelement;
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    pair<T> *newarray = new pair<T>[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

template<class T> void fifo<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    pair<T> *newarray = new pair<T>[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}


template<class T> void pair<T>::print_pairs(){
    cout << "(" << this->pair_t << "," << this->pair_n << ")" << endl;
}


// TODO
// pop_vip: removes the first pair (t_0, n_0) in the queue, for which n_0 is minimal,
//     and returns the element t_0.
template<class T> T fifo<T>::pop_vip(void)
{
    for()
}
 


int main(){
    //test #1
    fifo<int> f1;
    pair<int> p1(999,1);
    f1.pushback(p1);
    int ret1 = f1.pop_vip();
    cout <<"Test Case #1" << endl;  
    cout << "Expected Output: 999" << endl;   
    cout << ret1 << endl;
    cout << "Expected Output: true (1), the queue should be empty." << endl;
    cout << f1.isempty() << endl;
 
    //test #2
    //[(3,9),(0,7),(2,8),(5,3),(7,6),(8,5),(2,1),(9,4),(7,2),(10,0)]
    int input_t_list2[10] = {3,0,2,5,7,8,2,9,7,10};
    int input_n_list2[10] = {9,7,8,3,6,5,1,4,2,0};
    fifo<int> f2;
    for (int i=0; i<10; i++){
        pair<int> p2(input_t_list2[i],input_n_list2[i]);
        f2.pushback(p2);
    }
    int ret2 = f2.pop_vip();
    cout << endl << "Test Case #2" << endl;  
    cout << "Expected Output: 10" << endl;   
    cout << ret2 << endl;
    cout << "Expected Output: All pairs in the original order except (10, 0)." << endl;  
    pair<int> p2;
    for (int i=1; i <= f2.getlength(); i++){
        p2 = f2[i];
        p2.print_pairs();
    }


    //test #3
    int input_t_list3[11] = {8,94,12,-52,34,26,0,153,7,-33,27};
    int input_n_list3[11] = {5,2,3,9,7,8,1,4,-1,6,0};
    fifo<int> f3;
    for (int i=0; i<11; i++){
        pair<int> p3(input_t_list3[i],input_n_list3[i]);
        f3.pushback(p3);
    }
    int ret3 = f3.pop_vip();
    cout << endl << "Test Case #3" << endl;  
    cout << "Expected Output: 7" << endl;   
    cout << ret3 << endl;
    cout << "Expected Output: All pairs in the original order except (7,-1)." << endl;  
    pair<int> p3;
    for (int i=1; i <= f3.getlength(); i++){
        p3 = f3[i];
        p3.print_pairs();
    }

    return 0;
}
