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

void ranking(int a,int b,int c,int *best,int *good,int *fair){
    int temp;
    temp=(a>b)?a:b;
    *best=(temp>c)?temp:c;
    temp=(a<b)?a:b;
    *fair=(temp<c)?temp:c;
    if(a!=*best && a!=*fair){
        *good=a;
    }else if(b!=*best && b!=*fair){
        *good=b;
    }else{
        *good=c;
    }
}

void set_appointment(person *one,appointment *day){
    int pos_left=day->get_num();
    if(pos_left==0){
        cout<<"the hospitals have been fully occupied today,try tomorrow!\n";
        return;  
    }
    int *best,*good,*fair;
    ranking(one->preferred_hos1,one->preferred_hos2,one->preferred_hos3,best,good,fair);
    if(day->get_hos(*best)<5){
        one->apponitment_loc=*best;
        int x=day->get_hos(*best);
        one->treated_order=x+1;
        day->set_hos(*best,x+1);
    }else if(day->get_hos(*good)<5){
        one->apponitment_loc=*good;
        int x=day->get_hos(*good);
        one->treated_order=x+1;
        day->set_hos(*good,x+1);
    }else{
        one->apponitment_loc=*fair;
        int x=day->get_hos(*fair);
        one->treated_order=x+1;
        day->set_hos(*fair,x+1);
    }
    one->queueing=false;
    one->treated=false;
    one->appointed=true;
    day->set_num(pos_left-1);
}


