//
// Register.cpp Created by YayItsThunder on 2022.4.3
//

#include "Register.h"

// Return 0 means cannot open this file, retry is needed.
// Return 1 means open successfully.

person::person(void)
{
    id = -1;
    name = "";
    profession = -1;
    risk = -1;
    birth = "";
    age = -1;
    age_group = -1;
    address = "";
    phone = -1;
    wechat = "";
    email = "";
    register_order = -1;
    register_day = -1;
    preferred_hos1 = -1;
    preferred_hos2 = -1;
    preferred_hos3 = -1;
    apponitment_loc = -1;
    treated_order = -1;
    treated_date = -1;
    treated_time ="";
    if_treated = false;
    if_appointed = false;
    if_queueing = false;
}

int local_queue1_push_pop(int k , int register_process , person** input_array , Centralized_Queue<int> Fibo_heap)
{
    int day = (k + 1) / 2; // Ceiling
}