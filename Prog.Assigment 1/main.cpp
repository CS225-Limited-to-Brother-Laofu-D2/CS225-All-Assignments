//CA1 Group D2

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <queue>
using std::cout;
using std::cin;

#include "Register.cpp"
#include "FibHeap.h"
#include "appointment.cpp"

using namespace std;
//Include.h files and other .cpp files here

//weekly report:Treated people；Registered people with appointment；Queueing people without appointments
//(Including prof+age+risk+time)
int report_weekly (int Day, reg , cen, vector<appointment*> app )
{//choose the way to sort
int op,vnum = app.size();
cout << "Use what sort to output?"<<endl;
cout << "1. Sort by name"<<endl;
cout << "2. Sort by profession category"<<endl;
cout << "3. Sort by age group"<<endl;
cout << "Type anything but 1,2,3: Without any sort"<<endl;
cin>>op;

switch(op){
    case 1:
    for (int i=0; i < vnum; i++ ){
        app[i]->namesort();
    }break;
    case 2:
    for (int i=0; i < vnum; i++ ){
        app[i]->profsort();
    }break;
    case 3:
    for (int i=0; i < vnum; i++ ){
        app[i]->agesort();
    }break;
    default:
    break;
    
}
//Treated people given by appointments so far
person* per;
cout<<"Treated people this week"<<endl;
cout<<"name"<<" "<<"ID"<<" "<<"profession"<<" "<<"age"<<" "<<"risk"<<" "<<"waiting-time"<<endl;
for(int i=0; i<vnum; i++){
    per = app[i];
    int treat_time = Day - per->register_day;
    cout << per->name << " " << per->id << " "<< per->profession << " "<< per->age_group << " " << per->risk << " " << ;
}
    return 0;
}
//monthly report:Number of registered people; Number of waiting people (already in register); Number of appointments
int report_monthly (){
    
    return 0;
}
//------------------------------main function------------------------------
//1. Patients input

//2. Deal with queues and lists

//3. Report: Both weekly and monthly




int main()
{
    // Create two local queues.
    // These two local queues per day store 10 people each, i.e., total 20 people a day.
    queue<person*> localqueue_1;
    queue<person*> localqueue_2;

    // Create a double-pointer array, i.e, local_register is an array containing 500 pointers to class person.
    person** local_register;
    local_register = new person*[1500];
    for(int i = 0 ; i <= 1499 ; i++)
    {
        local_register[i] = new person;
    }

    // File open
    ifstream registry1("registry_1.csv", ios::in);
    if (!registry1)
    {
        cout << "Cannot open registry_1, program terminated." << endl;
        return 0;
    }
    string line;
    while(getline(registry1,line))
    {
        stringstream thisline(line);
        string everyblank;
        vector<string> patient_info;
        while(getline(thisline,everyblank,','))
        {
            patient_info.push_back(everyblank);
        }
        // Now patient_info is an array that stores a specific patient's information.
        int patient_id = atoi(patient_info[0].c_str());
        int index = patient_id - 1;
        local_register[index]->id = patient_id; // Minus 1 is needed since we want local_register[0] stores the first person.  
        local_register[index]->name = patient_info[1];
        local_register[index]->address = patient_info[2];
        local_register[index]->phone = atoi(patient_info[3].c_str());
        local_register[index]->email = patient_info[4];
        local_register[index]->wechat = patient_info[5];
        local_register[index]->profession = atoi(patient_info[6].c_str());
        local_register[index]->birth = patient_info[7];
        int patient_age = atoi(patient_info[8].c_str());
        local_register[index]->age = patient_age;
        int patient_age_group;
        if(patient_age <= 0)
        {
            cout<<"Umm, really?\n";
            patient_age_group = 0;
        }
        else
        {
            if(patient_age <= 12)
            {
                patient_age_group = 1; // Children group.
            }
            else
            {
                if(patient_age <= 18)
                {
                    patient_age_group = 2; // Adolenscents group.
                }
                else
                {
                    if(patient_age <= 35)
                    {
                        patient_age_group = 3; // Young adults group.
                    }
                    else
                    {
                        if(patient_age <= 50)
                        {
                            patient_age_group = 4; // Adults group.
                        }
                        else
                        {
                            if(patient_age <= 65)
                            {
                                patient_age_group = 5; // Seniors group.
                            }
                            else
                            {
                                if(patient_age <= 75)
                                {
                                    patient_age_group = 6; // Elderly people group.
                                }
                                else
                                {
                                    patient_age_group = 7; // Old people group.
                                }
                            }
                        }
                    }
                }
            }
        }
        local_register[index]->age_group = patient_age_group;  
        // Four risks 0 1 2 3 (no, low, medium, high)
        local_register[index]->risk = atoi(patient_info[9].c_str());
        local_register[index]->preferred_hos1 = atoi(patient_info[10].c_str());
        local_register[index]->preferred_hos2 = atoi(patient_info[11].c_str());
        local_register[index]->preferred_hos3 = atoi(patient_info[12].c_str());
        cout<<local_register[index]->name<<endl;
    }









    Centralized_Queue<int> haha;
    /*for appointment part */
    appointment** appoint_daily;
    appoint_daily = new appointment*[100];
    for(int i=0;i<100;i++){
        appoint_daily[i]=new appointment;
    }
    //for every day with treatment
    for(int t=0;t<100;t++){
        appointment *today;
        today=appoint_daily[t];
        int num_ddl=0;
        int count=0;
        //for every person
        for(int i=0;i<1500;i++){
            person one;
            one=*local_register[i];
            if(one.to_ddl==0 && one.if_treated==false && one.if_appointed==false && one.if_queueing==true)
                if(num_ddl<15){
                    set_appointment(local_register[i],today);
                    num_ddl++;
                    today->day_treat[count++]=local_register[i];
                }else{
                    cout<<"the hospitals today have been fully occupied\n";
                }
        }
        int pos_left=today->get_num();
        for(;pos_left>0;pos_left--){
            person *fib=haha.record_out();
            set_appointment(fib,today);
            today->day_treat[count++]=fib;
        }
        if ( (t+1) % 7 == 0 ){
            cout<<"\n"<<endl;
            cout<<"*******WEEKLY REPORT*******"<<endl;
            report_weekly (t, );
        }
        if ( (t+1) % 30 == 0 ){
            cout<<"\n"<<endl;
            cout<<"*******MONTHLY REPORT*******"<<endl;
            report_monthly (, );
        }
    }
    return 1;

int k; // This is the morning, afternoon counter.

for( k = 1 ; k <= 1000 ; k++)
{
    // Main loop here.
    int day = (k + 1) / 2; // Ceiling
    int morning_afternoon = k % 2;
    if(morning_afternoon = 0)
    {
        local_queue1_push(k,local_register);
    }
    if(morning_afternoon = 1)
    {
        local_queue2_push(k,local_register)
    }







}

    
}