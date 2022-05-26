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
#include "graphtraversal.cpp"
using std::cout;
using std::cin;

int main()
{
    // first graph
    digraphtraversal<int> * mygraph = new digraphtraversal<int>;
    (*mygraph).addedge(1,2);
    (*mygraph).addedge(1,3);
    (*mygraph).addedge(2,4);
    (*mygraph).addedge(3,4);
    (*mygraph).addedge(3,5);
    (*mygraph).addedge(5,6);
    (*mygraph).addedge(5,7);
    (*mygraph).addedge(5,8);
    (*mygraph).addedge(6,7);
    (*mygraph).addedge(8,9);
    (*mygraph).addedge(8,10);
    (*mygraph).prettyprint();
    searchtree<int> * mybfs = (*mygraph).bfs(1);
    (*mybfs).prettyprint();
    deepsearchtree<int> * mydfs = (*mygraph).dfs(1);
    (*mydfs).prettyprint();
    return 0;
}
