//
// Register.h Created by YayItsThunder on 2022.4.3
//

#ifndef Register_h
#define Register_h

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

#include "FibHeap.h"

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
        //how much does each person prefer hospital 1 to hospital 3
        //The priority of the hospital(if not full)
        int preferred_hos1; 
        int preferred_hos2;
        int preferred_hos3;
        //the appointed hospital location,date and time
        int apponitment_loc;
        int treated_order;
        int treated_date;
        string treated_time;
        //some symbols indicating the status of the person
        bool if_treated;
        bool if_appointed;
        bool if_queueing;
        bool if_withdrawed;
        bool if_re_registered;
        bool if_treated_locally;
        //Special situations
        int ddl_day;
        int wait_before_in_queue; // Only for medium risk.
        int wait_re_register;
        //Added
        int treatment_type;
        person(void);
        
};

// This function will return the register_process counter.
// Or return -1 means failure.
//int local_queue_push_pop(int k , int* register_counter, int register_process , person** input_array , Centralized_Queue<person*> Central_queue , queue<person*>* localqueue_1 , queue<person*>* localqueue_1_medium_risk , queue<person*>* localqueue_1_high_risk , queue<person*>* re_register_queue);


//The next four class are designed for the database, i.e., B+ and B tree.
class person_specific
{
    public:
        person_specific();
        int id;
        string name;
        int profession;
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
};

class medical_status
{
    public:
        medical_status();
        int risk;
        int treatment_type;
        int ddl_day;    
};

class registeration
{
    public:
        registeration();
        int register_order;
        int register_day;
        bool if_queueing;
        bool if_withdrawed;
        bool if_re_registered;
        int wait_before_in_queue;
        int wait_re_register;
};

class treatment
{
    public:
        treatment();
        int apponitment_loc;
        int treated_order;
        int treated_date;
        string treated_time;
        bool if_treated;
        bool if_appointed;
        bool if_treated_locally;
};

//person_union collects the pointers to four separate database 
class person_union
{
    public:
        person_union();
        person_specific *info;
        medical_status *status;
        registeration *reg;
        treatment *treat;
};

#endif