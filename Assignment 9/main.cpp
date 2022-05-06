#include <bits/stdc++.h>
using namespace std;
#include "bipartitegraph.cpp"
#include <iostream>
//this maintest.cpp is for basic tests for bfs, dfs and acyclic functions.
int main()
{
    //check the case of not perfect matching
    BIPARTITEGRAPH<int> graph_1;  
    graph_1.add_new_edge_pair(1,2);
    graph_1.add_new_edge_pair(3,2);
    graph_1.add_new_edge_pair(8,9);
    graph_1.add_new_edge_pair(2,1);
    graph_1.prettyprint();
    
    //check the case of perfect matching 
    BIPARTITEGRAPH<int> graph_2;  
    graph_2.add_new_edge_pair(5,6);
    graph_2.add_new_edge_pair(6,5);
    graph_2.add_new_edge_pair(9,8);
    graph_2.add_new_edge_pair(8,9);
    graph_2.prettyprint();
	return 0;
}

