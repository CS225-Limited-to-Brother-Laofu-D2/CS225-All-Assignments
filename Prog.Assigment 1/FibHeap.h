// This file contains three classes: FibNode, FibHeap, and CentralQueue.

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Register.h"

using namespace std;

template <class T> class FibNode;
template <class T> class FibHeap;
template <class T> class Centralized_Queue;

// FibNode is the nodes in the FibHeap.
template <class T> class FibNode{
    template <class X> friend class FibHeap;
    template <class Y> friend class Centralized_Queue;
    // definitions for friend classes.
public:
    T key;// This value is used for sorting.
    int degree;
    FibNode<T> *left;
    FibNode<T> *right;
    FibNode<T> *child; // the first child of the node
    FibNode<T> *parent;
    bool marked; // whether the first child is deleted or not

    FibNode(T value) {
        // constructor function
        key    = value;
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = nullptr;
        child  = nullptr;
    }
private:
    int id;
    string name;
    int profession;
    int risk;
    string birth;
    int age;
    int age_group;
    string address;
    int phone;
    string wechat;
    string email;
    int preferred_hos1;
    int preferred_hos2;
    int preferred_hos3;
    
    int priority;
    int dis_ddl; // when dis_ddl = 0, person will get the highest priority.
    string stat;
    int TreatDay;
    string RegData;
    int Reg_Day;
};

// Fibonacci Heap
template <class T> class FibHeap {
    template <class X> friend class CentralQueue;
    // definition for friend class.
public:
    FibHeap();// constructor function
    ~FibHeap();// destructor function
    
    void insert(FibNode<T> *node); // insert a node into the root list
    FibNode<T>* popMin(); // pop the min node from the heap
    void remove(FibNode<T> *node); // remove the node
    void combine(FibHeap<T> *other); // Merge other into the current heap
    
    void update(FibNode<T> *node, T key); // Update the Fibonacci heap oldkey to newkey
    bool contains(T key); // Whether the Fibonacci heap contains the key
    FibNode<T>* extractMin(); // remove the node with the minimum key, return a pointer to the node
    
    FibNode<T>* id_search(FibNode<T>* root, T key, int id); // search the node according to key and id
    void decrease(FibNode<T> *node, T key); // Decrease the value of the node who has the key in the Fibonacci heap
    void increase(FibNode<T> *node, T key); // Add the Fibonacci heap node to key
    bool minimum(T *min_key); // Get the minimum key value in the Fibonacci heap and save it to the min_key; success returns true, otherwise returns false.


private:
    int keyNum;         // the number of nodes in the heap
    int maxDegree;      // the maximum degree
    FibNode<T> *min;    // a pointer to the minimum node
    FibNode<T> **cons;    // the memory area of the maximum degree
    
private:
    void removeNode(FibNode<T> *node); // remove node from the double link list
    void addNode(FibNode<T> *node, FibNode<T> *root); // add node to the left of the root
    void link(FibNode<T>* node, FibNode<T>* root); // list node to the root list
    void makeCons(); // Create the space required for consolidate
    void consolidate(); // Merge trees of the same degree left and right in the root-linked table of the Fibonacci heap
    void renewDegree(FibNode<T> *parent, int degree); // update the degree
    void cut(FibNode<T> *node, FibNode<T> *parent); // Strip the node from the parent's child links and make the node a member of the root list
    void cascadingCut(FibNode<T> *node) ; // do cascading cut to the node
};

// CentralQueue is the class that other files need to call
// central queue contains a FibHeap, and some other functions
template <class T> class Centralized_Queue {

public:
    Centralized_Queue();
    // these are the functions needed in other files
    void set_date(int date); // set the date of tomorrow. Those people with medium risk or withdraw may released.
    void record_in(person *person); // transfer the data from local registry to center
    person *record_out(); // pop a "minimum" node
    void change_profession(person *person);
    void withdraw_heap(person *person);
    void sort(person *a);
    
private:
    int date; // tomorrow's date
    void transfer_in(person *person, FibNode<T> *fib_node); // transfer the data from person to fib_node
    void transfer_out(person *person, FibNode<T> *fib_node); // transfer the data from fib_node to person
    void search_node(person *person, FibHeap<T> **heap, FibNode<T> **fib_node); // search a node
    
    void build_array(person *a, FibNode<T> *root, int n);
   //  void build_vecotr(vector<Reg_Node> *a, FibNode<T> *root, int n);
    
    FibHeap<T> *fib_heap; // the central queue
};
