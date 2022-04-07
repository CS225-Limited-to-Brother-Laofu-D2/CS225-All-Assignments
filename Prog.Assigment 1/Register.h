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
        //the order and day for registration
        int register_order;
        int register_day;
        //how many days left from the deadline for treatment
        int to_ddl;
        //how much does each person prefer hospital 1 to hospital 3
        //The priority of the hospital(if not full)
        int preferred_hos1; 
        int preferred_hos2;
        int preferred_hos3;
        //the appointed hospital location,date and time
        int apponitment_loc;
        int treated_order;
        string treated_date;
        string treated_time;
        //some symbols indicating the status of the person
        bool if_treated;
        bool if_appointed;
        bool if_queueing;
        person(void);
        
};

// Return 0 means cannot deal with this file or some other wrong caused, retry or modification is needed.
// Return 1 means registed successfully.
int local_queue1_push_pop(int k , person** input_array);
int local_queue2_push_pop(int k , person** input_array);

#endif