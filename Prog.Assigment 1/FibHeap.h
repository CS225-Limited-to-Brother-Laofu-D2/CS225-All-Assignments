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
    person* loc; // loc is the pointer of the person
    int degree;
    FibNode<T> *left;
    FibNode<T> *right;
    FibNode<T> *child; // the first child of the node
    FibNode<T> *parent;
    bool marked; // whether the first child is deleted or not

    FibNode(person* pt) {
        // constructor function
        loc    = pt;
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = nullptr;
        child  = nullptr;
    }
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
    
    void updateProfession(FibNode<T> *node, int profession); // Update the Fibonacci heap old_risk to new_risk

    FibNode<T>* extractMin(); // remove the node with the minimum key, return a pointer to the node
    
    FibNode<T>* id_search(FibNode<T>* root, person* loc, int id); // search the node according to pointer and id
    void decreaseProfession(FibNode<T> *node, int profession); // Decrease the value of the node who has the risk in the Fibonacci heap
    void increaseProfession(FibNode<T> *node, int profession); // Add the Fibonacci heap node to risk
    bool minimum(T *highest_priority); // Get the highest priority in the Fibonacci heap and save it to the highest_priority; success returns true, otherwise returns false.
    bool ifempty(); // if empty retun ture, else retun false
    void print(); // Print the Fibonacci heap

private:
    int keyNum;         // the number of nodes in the heap
    int maxDegree;      // the maximum degree
    FibNode<T> *min;    // a pointer to the minimum node
    FibNode<T> **cons;    // the memory area of the maximum degree
    
private:
    int comparePriority(FibNode<T> *node0, FibNode<T> *node1); // if node0 has higher priority return 0, else return 1
    void removeNode(FibNode<T> *node); // remove node from the double link list
    void addNode(FibNode<T> *node, FibNode<T> *root); // add node to the left of the root
    void link(FibNode<T>* node, FibNode<T>* root); // list node to the root list
    void makeCons(); // Create the space required for consolidate
    void consolidate(); // Merge trees of the same degree left and right in the root-linked table of the Fibonacci heap
    void renewDegree(FibNode<T> *parent, int degree); // update the degree
    void cut(FibNode<T> *node, FibNode<T> *parent); // Strip the node from the parent's child links and make the node a member of the root list
    void cascadingCut(FibNode<T> *node) ; // do cascading cut to the node
    void print(FibNode<T> *node, FibNode<T> *prev, int direction); // Print "Fibonacci heap"
};

// CentralQueue is the class that other files need to call
// central queue contains a FibHeap, and some other functions
template <class T> class Centralized_Queue {

public:
    FibHeap<T> *fib_heap; // the central queue
    FibHeap<T> *withdraw_heap; // the heap for those who withdrawed
    // constructor function
    Centralized_Queue() {
        fib_heap = new FibHeap<T>;
        withdraw_heap = new FibHeap<T>;
        return;
    };
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
};
