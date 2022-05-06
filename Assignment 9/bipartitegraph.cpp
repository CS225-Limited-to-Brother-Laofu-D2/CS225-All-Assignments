//Written by group D2, with some reference to data stucture and algorithm written
//by Sartaj Sahni and the website https://www.geeksforgeeks.org/detect-cycle-in-a-graph/?ref=lbp in acyclic part 
using namespace std;
using std::endl;
#include <iostream>
#include <bits/stdc++.h>
#include "bipartitegraph.h"

/* make sets of unordered edges into sets of ordered pairs. */
template<class T> void BIPARTITEGRAPH<T>::girls_to_boys(T boy , T girl){
    //push a boy into a girl's adjacent list to create (g,b) pairs
    girls_adjlist[girl].push_back(boy);
    return; 
}

/* make sets of unordered edges into sets of ordered pairs. */
template<class T> void BIPARTITEGRAPH<T>::boys_to_girls(T boy , T girl){
    //push a girl into a boy's adjacent list to create (b,g) pairs
    boys_adjlist[boy].push_back(girl);
    return;
}

/* procedures for adding a pair */
template<class T> void BIPARTITEGRAPH<T>::add_new_edge_pair(T boy, T girl){
    boys_to_girls(boy, girl);
    girls_to_boys(boy, girl);
    pairs_count++;
    return;
}

/* procedures for deleting a pair*/
template<class T> void BIPARTITEGRAPH<T>::delete_boys_to_girls(T boy, T girl){
    boys_adjlist[boy].remove[girl];
    return;
}

/* procedures for deleting a pair*/
template<class T> void BIPARTITEGRAPH<T>::delete_girls_to_boys(T boy, T girl){
    girls_adjlist[girl].remove[boy];
    return;
}

/* procedures for deleting a pair*/
template<class T> void BIPARTITEGRAPH<T>::delete_edge_pair(T boy, T girl){
    delete_boys_to_girls(boy,girl);
    delete_girls_to_boys(boy,girl);
    pairs_count--;
    return;
}

/* unordered_boy makes ordered pairs into unordered edges */
template<class T> tuple<T,T> BIPARTITEGRAPH<T>::unordered_boy(T boy){
    T* pt_boys_adjlist=boys_adjlist[boy].begin();
    return make_tuple(boy,*pt_boys_adjlist);
}

/* unordered_girl makes ordered pairs into unordered edges */
template<class T> tuple<T,T> BIPARTITEGRAPH<T>::unordered_girl(T girl){
    T* pt_girls_adjlist=girls_adjlist[girl].begin();
    return make_tuple(girl,*pt_girls_adjlist);
}

/* obtain the numbers of boys and girls to be compared */
template<class T> void BIPARTITEGRAPH<T>::set_boys_count(){
    boys_count=0;
    map<int, list<int>>::iterator i;
    for(i=boys_adjlist.begin(); i!=boys_adjlist.end();i++){
       boys_count++;
    }
    return;
}

/* obtain the numbers of boys and girls to be compared */
template<class T> void BIPARTITEGRAPH<T>::set_girls_count(){
    girls_count=0;
    map<int, list<int>>::iterator i;
    for(i=girls_adjlist.begin(); i!=girls_adjlist.end();i++){
        girls_count++;
    }
    return;
}

/* verify if a boy or a girl is connected with only one girl or boy */
template<class T> bool BIPARTITEGRAPH<T>::only_one_boy(T girl){
    int count=0;
    list<int>::iterator i;
    for(i=girls_adjlist[girl].begin();i!=girls_adjlist[girl].end();i++){
        count++;
    }
    if (count==1){
        return true;
    }
    return false;
}

/* verify if a boy or a girl is connected with only one girl or boy */
template<class T> bool BIPARTITEGRAPH<T>::only_one_girl(T boy){
    int count=0;
    list<int>::iterator i;
    for(i=boys_adjlist[boy].begin();i!=boys_adjlist[boy].end();i++){
        count++;
    }
    if (count==1){
        return true;
    }
    return false;
}

//the following function checks if a map is perfect-matched
template<class T> bool BIPARTITEGRAPH<T>::is_perfect_matched(){
    set_boys_count();
    set_girls_count();
    //if the numbers are not the same, there are not perfect matching
    if (boys_count!=girls_count){ 
        return false;
    }
    map<int, list<int> > ::iterator i;
    for (i=boys_adjlist.begin();i!=boys_adjlist.end();++i){
        T curr_boy=i->first;
        //check if the boy only connect to one girl
        if (only_one_girl(curr_boy)==false){  
            return false;
        }
        T the_girl=*(boys_adjlist[curr_boy].begin());
        //conversely check if the girl connects to one boy
        if(only_one_boy(the_girl)==false){  
            return false;
        }
        T the_boy=*(girls_adjlist[the_girl].begin());
        //check if the boy connected is the boy we are looking at
        if (the_boy!=curr_boy){  
            return false;
        }
    }
    return true;
}

template<class T> void BIPARTITEGRAPH<T>::prettyprint(){
    cout<<"\nthis graph is";
    if (is_perfect_matched()){
        cout<<" perfect matched"<<endl;
    }
    else{
        cout<<" not perfect matched"<<endl;
    }
}

