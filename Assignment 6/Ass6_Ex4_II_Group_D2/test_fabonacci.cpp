#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fabonacci.cpp"
using std::cout;
using std::cin;
using std::hash;

int main(){
    int order;
    hashmap<int,int> myhashtable1;
    hashmap<int,int>(1);
    do
    {   
        cout<<"Please type the order you want in fabonacci sequence.\n";
        cin>>order;
        if(order < 0)
        {
            return 0;
        }
        int laofu = myhashtable1.fabonacci(order);    
        cout<<"the "<<order<<"th "<<"fabonacci number is "<<laofu<<"\n"; 
    }while(order >= 0);
    return 0;
}