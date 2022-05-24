//
//  test.cpp
//
//for testing the graph traversal class for directed graphs
//
//  Created by KD on 12.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "lgraph.cpp"
using std::cout;
using std::cin;

int main()
{
    // first graph
    ldigraph<int,double> * mygraph = new ldigraph<int,double>;
    (*mygraph).addedge(2,3,15);
    (*mygraph).addedge(1,4,7);
    (*mygraph).addedge(1,2,33);
    (*mygraph).addedge(3,4,11);
    (*mygraph).addedge(2,4,25);
    (*mygraph).addvertex(7);
    (*mygraph).addedge(3,7,31);
    (*mygraph).addedge(7,2,100);
    (*mygraph).prettyprint();
    (*mygraph).addedge(1,4,13);
    (*mygraph).prettyprint();
    
    // second graph
    ldigraph<int,double> * yourgraph = new ldigraph<int,double>;
    (*yourgraph).addedge(1,2,5);
    (*yourgraph).addedge(2,3,8);
    (*yourgraph).addedge(1,3,22);
    (*yourgraph).addedge(1,4,73);
    (*yourgraph).addedge(4,5,17);
    (*yourgraph).addedge(5,6,4);
    (*yourgraph).addedge(6,4,15);
    (*yourgraph).addedge(6,7,42);
    (*yourgraph).addedge(6,8,43);
    (*yourgraph).addedge(6,9,37);
    (*yourgraph).addedge(8,10,13);
    (*yourgraph).addedge(10,4,51);
    (*yourgraph).prettyprint();
    return 0;
}
