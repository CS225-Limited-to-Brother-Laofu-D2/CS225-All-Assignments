#ifndef bipartitegraph
#define bipartitegraph
using namespace std;
#include <tuple>
#include <bits/stdc++.h>
#include <iostream>
template<class T> class BIPARTITEGRAPH{//Directed graph
    public:
    tuple<T,T> pair;//a pair of 
    int pairs_count=0;
    int boys_count=0;
    int girls_count=0;
    
    map<T, list<T>> boys_adjlist;//adjacency list of boys
    map<T, list<T>> girls_adjlist;//adjacency list of girls
    
    void girls_to_boys(T boy,T girl);
    void boys_to_girls(T boy,T girl);
    void add_new_edge_pair(T boy,T girl);
    void delete_girls_to_boys(T boy,T girl);
    void delete_boys_to_girls(T boy,T girl);
    void delete_edge_pair(T boy,T girl);
    tuple<T,T> unordered_boy(T boy);
    tuple<T,T> unordered_girl(T girl);
    //get the number of boys in map adjlistboys
    void set_boys_count(void);
    void set_girls_count(void);
    bool is_perfect_matched(void);//return true if this bipartitegraph is perfectly matched
    bool only_one_girl(T boy);//return true if this boy has only one edge to one girl
    bool only_one_boy(T girl);
 
    void prettyprint();

};
#endif