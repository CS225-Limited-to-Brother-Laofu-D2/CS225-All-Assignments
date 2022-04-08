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

int local_queue1_push_pop(int k , int register_process , person** input_array , Centralized_Queue<int> Fibo_heap , queue<person*> localqueue_1)
{
    int day = (k + 1) / 2;
    int counter ;
    for(counter = 1 ; counter <= 20 ; counter++)
    {
        person* person_now_process = input_array[register_process + counter];
        if(person_now_process->risk == 0 || person_now_process->risk == 1)// no or low risk
        {
            localqueue_1.push(person_now_process);
            person_now_process->if_queueing = true;
            person_now_process->register_day = day;
            person_now_process->ddl_day = day + 20; // We suppoose the ddl is 20 days
        }
        else
        {
            if(person_now_process->risk == 2) // medium risk
            {

            }
            else
            {
                if(person_now_process->risk == 3) // Hight risk
                {

                }
                else
                {
                    cout<<"Error detected, this person cannot be registered."<<endl;
                    return -1;
                }
            }
        }
    }
}