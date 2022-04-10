//
//  test.cpp
//
//  Created by KD on 15.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bst.cpp"
using std::cout;
using std::cin;

int main()
{
    BST<int> *mytree = new BST<int>;
    // testing insert
    (*mytree).insert(0);
    (*mytree).insert(-4);
    (*mytree).insert(1);
    (*mytree).insert(2);
    (*mytree).insert(-8);
    (*mytree).insert(30);
    (*mytree).insert(42);
    (*mytree).insert(3);
    (*mytree).insert(4);
    (*mytree).insert(5);
    (*mytree).insert(-1);
    (*mytree).insert(6);
    (*mytree).insert(55);
    (*mytree).insert(9);
    (*mytree).insert(-7);
    (*mytree).insert(187);
    (*mytree).insert(-6);
    (*mytree).insert(79);
    (*mytree).insert(-5);
    (*mytree).insert(264);
    (*mytree).insert(7);
    (*mytree).insert(-3);
    (*mytree).insert(8);
    (*mytree).insert(-2);
    (*mytree).insert(56);
    (*mytree).prettyprint();
    cout << "=========\n";
    // testing delete
    (*mytree).remove(42);
    (*mytree).remove(56);
    (*mytree).remove(13);
    (*mytree).remove(-4);
    (*mytree).remove(7);
    (*mytree).remove(0);
    (*mytree).remove(14);
    (*mytree).prettyprint();
    return(0);
}
