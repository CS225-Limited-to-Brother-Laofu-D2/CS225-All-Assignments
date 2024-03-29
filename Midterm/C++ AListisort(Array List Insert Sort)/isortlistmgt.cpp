//
//  sortlistmgt.cpp
//  
//
//  Created by KD on 22.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alistisort.cpp"
using std::cout;
using std::cin;

int main()
{
    int type, size, op;
    int pos, yes;
    int intitem, result1;
    AList<int> mylist1;
    AList<double> mylist2;
    double doubleitem, result2;
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
    cout << "Enter a positive integer for the size of your list:\n";
    cin >> size;
    if (size <= 0)
        size = 20;
    switch(type)
    {
        case 0:
        {
            AList<int> mylist1 = AList<int>(size);
            break;
        }
        case 1:
        {
            AList<double> mylist2 = AList<double>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: append\n";
            cout << "2: insert\n";
            cout << "3: delete\n";
            cout << "4: set\n";
            cout << "5: get\n";
            cout << "6: in\n";
            cout << "7: length\n";
            cout << "8: concat\n";
            cout << "9: sublist\n";
            cout << "10: equal\n";
            cout << "11: sort\n";
            cout << "12: display\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 12));
        switch(op)
        {
            case 0: return(0);
            case 1:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.append(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.append(doubleitem);
                }
                break;
            }
            case 2:
            {
                cout << "Enter a position and a value:\n";
                cin >> pos;
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.insert(pos, intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.insert(pos, doubleitem);
                }
                break;
            }
            case 3:
            {
                cout << "Enter a position:\n";
                cin >> pos;
                if (type == 0)
                    mylist1.remove(pos);
                else
                    mylist2.remove(pos);
                break;
            }
            case 4:
            {
                cout << "Enter a position and a value:\n";
                cin >> pos;
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.setitem(pos, intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.setitem(pos, doubleitem);
                }
                break;
            }
            case 5:
            {
                cout << "Enter a position:\n";
                cin >> pos;
                if (type == 0)
                {
                    result1 = mylist1.getitem(pos);
                    cout << result1 << "\n";
                }
                else
                {
                    result2 = mylist2.getitem(pos);
                    cout << result2 << "\n";
                }
                break;
            }
            case 6:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    boolresult = mylist1.member(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    boolresult = mylist2.member(doubleitem);
                }
                cout << boolresult << "\n";
                break;
            }
            case 7:
            {
                if (type == 0)
                    result1 = mylist1.getlength();
                else
                    result1 = mylist2.getlength();
                cout << result1 << "\n";
                break;
            }
            case 8:
            {
                if (type == 0)
                {
                    AList<int> mylistnew1 = AList<int>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> intitem;
                            mylistnew1.append(intitem);
                        }
                    }
                    while (yes == 1);
                    mylist1.concat(mylistnew1);
                }
                else
                {
                    AList<double> mylistnew2 = AList<double>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> doubleitem;
                            mylistnew2.append(doubleitem);
                        }
                    }
                    while (yes == 1);
                    mylist2.concat(mylistnew2);
                }
                break;
            }
            case 9:
            {
                if (type == 0)
                {
                    AList<int> mylistnew1 = AList<int>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> intitem;
                            mylistnew1.append(intitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist1.sublist(mylistnew1);
                }
                else
                {
                    AList<double> mylistnew2 = AList<double>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> doubleitem;
                            mylistnew2.append(doubleitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist2.sublist(mylistnew2);
                }
                if (boolresult == true)
                {
                    cout << "The new list is a sublist.\n";
                }
                else
                    cout << "The new list is not a sublist.\n";
                break;
            }
            case 10:
            {
                if (type == 0)
                {
                    AList<int> mylistnew1 = AList<int>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> intitem;
                            mylistnew1.append(intitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist1.equal(mylistnew1);
                }
                else
                {
                    AList<double> mylistnew2 = AList<double>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> doubleitem;
                            mylistnew2.append(doubleitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist2.sublist(mylistnew2);
                }
                if (boolresult == true)
                {
                    cout << "The new list is equal.\n";
                }
                else
                    cout << "The new list is not equal.\n";
                break;
            }
            case 11:
            {
                if (type == 0)
                    mylist1.isort();
                /* alternatively, use the in-place function: mylist1.isort_ip(); */
                else
                    mylist2.isort();
                    /* alternatively, use the in-place function: mylist1.isort_ip(); */
                break;
            }
            case 12:
            {
                if (type == 0)
                {
                    int numelements = mylist1.getlength();
                    for (int i = 1; i <= numelements; ++i)
                    {
                        intitem = mylist1[i];
                        cout << "List element " << i << " is " << intitem <<".\n";
                    }
                }
                else
                {
                    int numelements = mylist2.getlength();
                    for (int i = 1; i <= numelements; ++i)
                    {
                        doubleitem = mylist2[i];
                        cout << "List element " << i << " is " << doubleitem <<".\n";
                    }
                }
                break;
            }
            default: return(0);
        }
    }
    while (op != 0);
    return(0);
}
