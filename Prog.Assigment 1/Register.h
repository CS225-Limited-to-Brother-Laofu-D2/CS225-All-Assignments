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
        //Special situations
        int ddl_day;
        person(void);
        
};

// These two functions will return the register_process counter
// Or return -1 means failure.
int local_queue1_push_pop(int k , int register_process , person** input_array , Centralized_Queue<int> Fibo_heap , queue<person*> localqueue_1;);
int local_queue2_push_pop(int k , int register_process , person** input_array , Centralized_Queue<int> Fibo_heap , queue<person*> localqueue_2;);

#endif