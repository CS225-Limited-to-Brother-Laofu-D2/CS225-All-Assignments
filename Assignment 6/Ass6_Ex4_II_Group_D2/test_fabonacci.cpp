#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fabonacci.cpp"
using std::cout;
using std::cin;
using std::hash;

int main(){
    int order;
    cin>>order;
    hashmap<int,int> myhashtable1;
    cout<<"the "<<order<<"th "<<"fabonacci number is "<<myhashtable1.fabonacci(order);
    return 0;
}