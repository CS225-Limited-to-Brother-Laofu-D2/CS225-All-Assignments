//
// Register.cpp Created by YayItsThunder on 2022.4.3
//

#include "Register.h"

// Return 0 means cannot open this file, retry is needed.
// Return 1 means open successfully.

person::person(void)
{

}

int regist(void)
{
    ifstream registry1("registry_1.csv", ios::in);
    if (!registry1)
    {
        cout << "Cannot open registry_1, please retry." << endl;
        return 0;
    }
    ifstream registry2("registry_2.csv", ios::in);
    if (!registry2)
    {
        cout << "Cannot open registry_2, please retry." << endl;
        return 0;
    }
    
}