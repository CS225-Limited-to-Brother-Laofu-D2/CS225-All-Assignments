//
// Register.h Created by YayItsThunder on 2022.4.3
//

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

class person
{
    public:
        int id;
        string name;
        int profession;
        int risk;
        string birth;
        int age;
        int age_group;
        string address;
        int phone;
        string wechat;
        string email;

        int preferred_hos1;
        int preferred_hos2;
        int preferred_hos3;

        person(void);
        
};

// Return 0 means cannot deal with this file or some other wrong caused, retry or modification is needed.
// Return 1 means registed successfully.
int regist(ifstream filename, person** input_array);