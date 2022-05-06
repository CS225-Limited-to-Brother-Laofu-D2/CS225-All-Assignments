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
#include "graphtraversal.cpp"
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
    mygraph->addedge(9,10);
    mygraph->prettyprint();
    searchforest<int>* newbfs = mygraph->newbfs(1);
    newbfs->prettyprint();
    deepsearchforest<int>* newdfs = mygraph->newdfs(1);
    newdfs->prettyprint();
    bool if_acyclic = mygraph->is_acyclic();
    if(if_acyclic)
    {
        cout<<"This graph is acyclic, i.e., it does not contain a cycle"<<endl;
    }
    else
    {
        cout<<"This graph is not acyclic, i.e., it contains at least one cycle"<<endl;  
    }
    // second graph
    graphtraversal<int> * yourgraph = new graphtraversal<int>;
    yourgraph->addedge(1,2);
    yourgraph->addedge(1,3);
    yourgraph->addedge(3,4);
    yourgraph->addedge(4,2);
    yourgraph->addedge(2,5);
    yourgraph->prettyprint();
    newbfs = mygraph->newbfs(1);
    newbfs->prettyprint();
    newdfs = mygraph->newdfs(1);
    newdfs->prettyprint();
    bool nice = yourgraph->is_acyclic();
    if(nice)
    {
        cout<<"This graph is acyclic, i.e., it does not contain a cycle"<<endl;
    }
    else
    {
        cout<<"This graph is not acyclic, i.e., it contains at least one cycle"<<endl;  
    }
    return 0;
}
