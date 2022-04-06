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
using std::cout;
using std::cin;
using std::endl;

#ifndef Register_h
#define Register_h
    
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
        //how much does each person prefer hospital 1 to hospital 3
        //"1" represents prefer most, while "3" indicates prefer least
        int preferred_hos1; 
        int preferred_hos2;
        int preferred_hos3;
        //the appointed hospital location,date and time
        int apponitment_loc;
        string treated_date;
        string treated_time;
        //some symbols indicating the status of the person
        bool treated;
        bool appointed;
        bool queueing;
        person(void);
        
};

// Return 0 means cannot deal with this file or some other wrong caused, retry or modification is needed.
// Return 1 means registed successfully.
int regist(ifstream filename, person** input_array);

#endif