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
    ddl_day = -1;
    wait_before_in_queue = -1;
}

int local_queue1_push_pop(int k , int register_process , person** input_array , Centralized_Queue<int> Fibo_heap , queue<person*> localqueue_1 , queue<person*> localqueue_1_medium_risk , queue<person*> localqueue_1_high_risk)
{
    int day = (k + 1) / 2;
    int counter ; // Every half day we only process 10 people.
    while(!localqueue_1_medium_risk.empty() && localqueue_1_medium_risk.front()->wait_before_in_queue == day)
    {
        person* medium_person_process = localqueue_1_medium_risk.front();
        localqueue_1_medium_risk.pop(); // We found a meidum risk people that need to push into the local queue.
        localqueue_1.push(medium_person_process);
        medium_person_process->if_queueing = true;
        medium_person_process->register_day = day;
        medium_person_process->register_day = day + 20;
        counter++;
        register_process++;
        if(localqueue_1_medium_risk.empty())
        {
            break;
        }
    }
    if(Fibo_heap)
    {

    }
    for(/*nothing here*/; counter <= 10 ; counter++)
    {
        person* person_now_process = input_array[register_process + counter];
        if(person_now_process->risk == 0 || person_now_process->risk == 1)// no or low risk
        {
            localqueue_1.push(person_now_process);
            person_now_process->if_queueing = true;
            person_now_process->register_day = day;
            person_now_process->ddl_day = day + 20; // We suppoose the ddl is 20 days
            register_process++;
        }
        else
        {
            if(person_now_process->risk == 2) // medium risk
            {
                person_now_process->wait_before_in_queue = day + 30;
                localqueue_1_medium_risk.push(person_now_process);
                counter--; // We didnt process people this time.
                register_process++;
            }
            else
            {
                if(person_now_process->risk == 3) // Hight risk
                {
                    localqueue_1_high_risk.push(person_now_process);
                    counter--; // We didnt process people this time.
                    register_process++;
                }
                else
                {
                    cout<<"Error detected, this person cannot be registered."<<endl;
                    return -1;
                }
            }
        }
    }
    // Local queue process ended, now need to pop into fibo heap(centralized queue)
    while(!localqueue_1.empty())
    {
        person* person_push_into = localqueue_1.front()
    }
    return register_process;
}