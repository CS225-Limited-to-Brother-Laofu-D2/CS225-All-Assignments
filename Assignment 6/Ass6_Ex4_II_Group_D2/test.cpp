#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.cpp"
using std::cout;
using std::cin;
using std::hash;

int main()
{
    int type, size, op;
    hashmap<int,int> myhashtable1;
    hashmap<int,double> myhashtable2;
    bool boolresult;
    do
    {
        cout << "Choose your element type:\n";
        cout << "0: int  1: double\n";
        cin >> type ;
        if ((type != 0) && (type != 1))
            cout << "You must choose 0 or 1\n\n";
    }
    while ((type != 0) && (type != 1));
    cout << "Enter a positive integer for the size of your hashtable:\n";
    cin >> size;
    switch(type)
    {
        case 0:
        {
            myhashtable1 = hashmap<int,int>(size);
            break;
        }
        case 1:
        {
            myhashtable2 = hashmap<int,double>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: add\n";
            cout << "2: delete\n";
            cout << "3: member\n";
            cout << "4: display\n";
            cout << "5: retrieve\n";
            cin >> op;
        }
        while ((op < 0) && (op > 5));
        switch(op)
        {
            case 0: return(0);
            case 1:
            {
                cout << "Enter the key and value:\n";
                if (type == 0)
                {
                    int intkey;
                    cin>>intkey;
                    int intitem;
                    cin >> intitem;
                    myhashtable1.add(intkey,intitem);
                }
                else
                {
                    int intkey;
                    cin >> intkey;
                    double doubleitem;
                    cin >> doubleitem;
                    myhashtable2.add(intkey,doubleitem);
                }
                break;
            }
            case 2:
            {
                cout << "Enter a key:\n";
                if (type == 0)
                {
                    int intkey;
                    cin >> intkey;
                    myhashtable1.remove(intkey);
                }
                else
                {
                    int intkey;
                    cin >> intkey;
                    myhashtable2.remove(intkey);
                }
                break;
            }
            case 3:
            {
                cout << "Enter the key and value:\n";
                if (type == 0)
                {
                    int intkey;
                    cin >> intkey;
                    int intitem;
                    cin >> intitem;
                    boolresult = myhashtable1.member(intkey,intitem);
                }
                else
                {
                    int intkey;
                    cin >> intkey;
                    double doubleitem;
                    cin >> doubleitem;
                    boolresult = myhashtable2.member(intkey,doubleitem);
                }
                if (boolresult == true)
                    cout << "The value is in the hashtable.\n";
                else
                    cout << "The value is not in the hashtable.\n";
                break;
            }
            case 4:
            {
                if (type == 0)
                    myhashtable1.display();
                else
                    myhashtable2.display();
                break;
            }
            case 5:
            {
                int intkey;
                cout<<"Enter the key\n";
                if(type == 0){
                    cin>>intkey;
                    cout<< "the value is "<<myhashtable1.retrieve(intkey)<<"\n";
                }else{
                    cin>>intkey;
                    cout<< "the value is "<<myhashtable2.retrieve(intkey)<<"\n";
                }
            }
        }
    }
    while (op != 0);
    return(0);
}
