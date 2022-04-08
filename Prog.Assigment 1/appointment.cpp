#include"Register.h"
#include"appointment.h"
#include"FibHeap.h"

void appointment::set_num(int num){
    num_left=num;
}

int appointment::get_num(){
    return num_left;
}

void appointment::set_hos(int order,int num){
    each_hos_filled[order]=num;
}

int appointment::get_hos(int order){
    return each_hos_filled[order];
}

appointment::appointment(/* args */)
{
    each_hos_filled=new int[3];
    for(int i=0;i<3;i++){
        each_hos_filled[i]=0;
    }
    set_num(15);
    day_treat=new person*[15];
    for(int i=0;i<15;i++){
        day_treat[i]=new person;
    }
}

void appointment::agesort()
{
    // get the length of the queue p
    int len=p->size();
    person a[len]; // use a[] to store reg node from the queue
    // char b[len];
    person *p1;
    person *p2;

    // store and pop every element from the queue
    for (int i = 0; i < len; ++i)
    {
        a[i] = p->front();
        p->pop();
    }

    // use selection sort to sort based on the age
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            p1 = &a[max];
            p2 = &a[j];

            // if p1 larger than p2, swap them
            if (p1->get_age() < p2->get_age())
            {
                max=j;
            }
        }
        person tmp = a[i];
        a[i] = a[max];
        a[max] = tmp;
    }
    for (int i=0; i< len; ++i)
    {
        p->push(a[i]);
    }
    // return p;
}

// sorting according to name
void appointment::namesort()
{
    int len=p->size();
    person a[len];
    // char b[len];
    person *p1;
    person *p2;

    for (int i = 0; i < len; ++i)
    {
        a[i] = p->front();
        p->pop();
    }

    // use selection sort to sort based on the name
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            p1 = &a[max];
            p2 = &a[j];

            // if p1 larger than p2, swap them
            if(p1->get_name() < p2->get_name())
            {
                max=j;
            }
        }
        person tmp = a[i];
        a[i] = a[max];
        a[max] = tmp;
    }

    for (int i=0; i< len; ++i)
    {
        p->push(a[i]);
    }
    // return p;
}


// sort according to profession
void appointment::profsort()
{
    // get the length of the queue p
    int len=p->size();
    person a[len]; // use a[] to store reg node from the queue
    // char b[len];
    person *p1;
    person *p2;

    // store and pop every element from the queue
    for (int i = 0; i < len; ++i)
    {
        a[i] = p->front();
        p->pop();
    }

    // use selection sort to sort based on the profession
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            p1 = &a[max];
            p2 = &a[j];

            // if p1 larger than p2, swap them
            if (p1->get_profession() < p2->get_profession())
            {
                max=j;
            }
        }
        person tmp = a[i];
        a[i] = a[max];
        a[max] = tmp;
    }
    for (int i=0; i< len; ++i)
    {
        p->push(a[i]);
    }
    // return p;
}



void set_appointment(person *one,appointment *day){
    int pos_left=day->get_num();
    if(pos_left==0){
        cout<<"the hospitals have been fully occupied today,try tomorrow!\n";
        return;  
    }
    int best=one->preferred_hos1;
    int good=one->preferred_hos2;
    int fair=one->preferred_hos3;
    if(day->get_hos(best)<5){
        one->apponitment_loc=best;
        int x=day->get_hos(best);
        one->treated_order=x+1;
        day->set_hos(best,x+1);
    }else if(day->get_hos(good)<5){
        one->apponitment_loc=good;
        int x=day->get_hos(good);
        one->treated_order=x+1;
        day->set_hos(good,x+1);
    }else{
        one->apponitment_loc=fair;
        int x=day->get_hos(fair);
        one->treated_order=x+1;
        day->set_hos(fair,x+1);
    }
    one->if_queueing=false;
    one->if_treated=false;
    one->if_appointed=true;
    day->set_num(pos_left-1);
}
