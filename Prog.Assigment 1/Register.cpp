//
// Register.cpp Created by YayItsThunder on 2022.4.3
//

#include "Register.h"
#include "FibHeap.h"

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
    if_withdrawed = false;
    if_re_registered = false;
    ddl_day = -1;
    wait_before_in_queue = -1;
}

int local_queue_push_pop(int k , int* register_counter , int register_process , person** input_array , Centralized_Queue<person*> Central_queue , queue<person*>* localqueue_1 , queue<person*>* localqueue_1_medium_risk , queue<person*>* localqueue_1_high_risk , queue<person*>* re_register_queue)
{
    int day = (k + 1) / 2;
    int counter = 0; // Every half day we only process 10 people.
    while(!localqueue_1_medium_risk->empty() && localqueue_1_medium_risk->front()->wait_before_in_queue == day && counter <= 10)
    {
        person* medium_person_process = localqueue_1_medium_risk->front();
        localqueue_1_medium_risk->pop(); // We found a meidum risk people that need to push into the local queue.
        localqueue_1->push(medium_person_process);
        medium_person_process->if_queueing = true;
        medium_person_process->register_day = day;
        medium_person_process->ddl_day = day + 20;
        *register_counter++;
        counter++;
    }
    if(Central_queue.fib_heap->ifempty()) // In this case, we can process with the people with high risk.
    {
        while(!localqueue_1_high_risk->empty() && counter <= 10)
        {
            person* high_person_process = localqueue_1_high_risk->front();
            localqueue_1_high_risk->pop();
            localqueue_1->push(high_person_process);
            high_person_process->if_queueing = true;
            high_person_process->register_day = day;
            high_person_process->ddl_day = day + 20;
            *register_counter++;
            counter++;
        }
    }
    // We also need to deal with the people who withdrawed then registered.
    // Say that they have waited for enough days.
    while(!re_register_queue->empty() && re_register_queue->front()->wait_re_register == day && counter <= 10)
    {
        person* re_register_person_process = re_register_queue->front();
        re_register_queue->pop();
        localqueue_1->push(re_register_person_process);
        re_register_person_process->if_queueing = true;
        re_register_person_process->if_re_registered = false;
        re_register_person_process->if_withdrawed = false;
        re_register_person_process->register_day = day;
        re_register_person_process->ddl_day = day + 20;
        *register_counter++;
        counter++;
    }
    for(/*nothing here*/; counter <= 10 ; counter++)
    {
        person* person_now_process = input_array[register_process];
        if(person_now_process->risk == 0 || person_now_process->risk == 1)// no or low risk
        {
            localqueue_1->push(person_now_process);
            person_now_process->if_queueing = true;
            person_now_process->register_day = day;
            person_now_process->ddl_day = day + 20; // We suppoose the ddl is 20 days
            *register_counter++;
            register_process++;
        }
        else
        {
            if(person_now_process->risk == 2) // medium risk
            {
                person_now_process->wait_before_in_queue = day + 30;
                localqueue_1_medium_risk->push(person_now_process);
                counter--; // We didn't push people into queue this time.
                register_process++;
            }
            else
            {
                if(person_now_process->risk == 3) // Hight risk
                {
                    localqueue_1_high_risk->push(person_now_process);
                    counter--; // We didn't push people into queue this time.
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
    while(!localqueue_1->empty())
    {
        person* person_push_into = localqueue_1->front();
        localqueue_1->pop();
        Central_queue.record_in(person_push_into);
    }
    return register_process;
}