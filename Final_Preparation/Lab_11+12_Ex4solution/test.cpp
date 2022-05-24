//
//  test.cpp
//
//for testing the graph traversal class
//
//  Created by KD on 12.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "greedy.cpp"
using std::cout;
using std::cin;

int main()
{
    // first graph
    graphtraversal<int> * mygraph = new graphtraversal<int>;
    (*mygraph).addedge(2,3);
    (*mygraph).addedge(1,4);
    (*mygraph).addedge(1,2);
    (*mygraph).addedge(3,4);
    (*mygraph).addedge(2,4);
    (*mygraph).addvertex(7);
    (*mygraph).addedge(3,7);
    (*mygraph).addedge(7,2);
    (*mygraph).addedge(1,4);
    (*mygraph).prettyprint();
    cout << "------\n";
    deepsearchtree<int> * mydfs = (*mygraph).colouring();
    (*mygraph).prettyprint();
    (*mygraph).uncolour();
    (*mygraph).greedycolouring();
    (*mygraph).prettyprint();
    // second graph
    graphtraversal<int> * yourgraph = new graphtraversal<int>;
    (*yourgraph).addedge(1,2);
    (*yourgraph).addedge(2,3);
    (*yourgraph).addedge(1,3);
    (*yourgraph).addedge(1,4);
    (*yourgraph).addedge(4,5);
    (*yourgraph).addedge(5,6);
    (*yourgraph).addedge(6,4);
    (*yourgraph).addedge(6,7);
    (*yourgraph).addedge(6,8);
    (*yourgraph).addedge(6,9);
    (*yourgraph).addedge(8,10);
    (*yourgraph).addedge(10,4);
    (*yourgraph).prettyprint();
    cout << "------\n";
    deepsearchtree<int> * yourdfs = (*yourgraph).colouring();
    (*yourgraph).prettyprint();
    (*yourgraph).uncolour();
    (*yourgraph).greedycolouring();
    (*yourgraph).prettyprint();
    // third graph
    graphtraversal<int> * newgraph = new graphtraversal<int>;
    (*newgraph).addedge(1,2);
    (*newgraph).addedge(1,4);
    (*newgraph).addedge(2,5);
    (*newgraph).addedge(6,3);
    (*newgraph).addedge(3,4);
    (*newgraph).addedge(4,7);
    (*newgraph).addedge(5,8);
    (*newgraph).addedge(6,5);
    (*newgraph).prettyprint();
    cout << "------\n";
    deepsearchtree<int> * newdfs = (*newgraph).colouring();
    (*newgraph).prettyprint();
    (*newgraph).uncolour();
    (*newgraph).greedycolouring();
    (*newgraph).prettyprint();
    cout << "------\n";
    return 0;
}
