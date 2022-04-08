//CA1 Group D2

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <queue>
using std::cout;
using std::cin;

#include "Register.cpp"
#include "FibHeap.cpp"
#include "appointment.cpp"

using namespace std;
//Include.h files and other .cpp files here

//weekly report:Treated people；Registered people with appointment；Queueing people without appointments
//(Including prof+age+risk+time)
int report_weekly (int Day, appointment **appoint_daily)
{//choose the way to sort
int op,vnum = app.size();
int category;
cout<<"which category do you want to sort?\n";
cout<<"Enter 1 for treated people, 2 for appointed people, 3 for queueing people\n";
cin>>category;
cout << "Use what sort to output?"<<endl;
cout << "1. Sort by name"<<endl;
cout << "2. Sort by profession category"<<endl;
cout << "3. Sort by age group"<<endl;
cout << "Type anything but 1,2,3: Without any sort"<<endl;
cin>>op;

switch(op){
    case 1:
    for (int i=0; i < vnum; i++ ){
        //app[i]->namesort();
    }break;
    case 2:
    for (int i=0; i < vnum; i++ ){
       // app[i]->profsort();
    }break;
    case 3:
    for (int i=0; i < vnum; i++ ){
        //app[i]->agesort();
    }break;
    default:
    break;
   
}
//Treated people given by appointments so far
cout<<"Treated people this week"<<endl;
cout<<"name"<<" "<<"ID"<<" "<<"profession"<<" "<<"age"<<" "<<"risk"<<" "<<"waiting-time"<<endl;

int week=Day/7;
int begin_day=(week-1)*7;
    for(int i=0;i<=5;i++){
        appointment *now_day=appoint_daily[begin_day+i];
        for(int j=0;j<15;j++){
            person *reported=now_day->day_treat[j];
            cout<<reported->name<<" "<<reported->id<<" "<<reported->profession<<" "<<reported->age_group<<" "<<reported->risk<<" "<<reported->treated_date-reported->register_day<<endl;
        }
    }
cout<<"\n"<<endl;
//Waiting people with appointments (lists from three hospitals)
cout<<"Waiting people with appointments this week"<<endl;
cout<<"name"<<" "<<"ID"<<" "<<"profession"<<" "<<"age"<<" "<<"risk"<<" "<<"waiting-time-until-today"<<endl;
appointment *now_day=appoint_daily[begin_day+6];
    for(int j=0;j<15;j++){
        person *reported=now_day->day_treat[j];
        cout<<reported->name<<" "<<reported->id<<"  "<<reported->profession<<" "<<reported->age_group<<"  "<<reported->risk<<" "<<reported->treated_date-reported->register_day<<endl;
    }

cout<<"\n";
//Queueing people without apppointments (all the poeple in centralized queue(Fib-heap))
cout<<"Queueing poeple without appointments this week"<<endl;
cout<<"name"<<" "<<"ID"<<" "<<"profession"<<" "<<"age"<<" "<<"risk"<<" "<<"waiting-time-until-today"<<endl;


cout<<"\n";

cout<<"Weekly Report is done"<<endl;
    
    
    return 0;
}
//monthly report:Number of registered people; Number of waiting people (already in register); Number of appointments
int report_monthly (int num_appoint,int* reg, double av_time){
    //number of registered people
    cout<<"The number of registered people is: "<<*reg<<endl;
    //number of waiting people

    //number of treatment appointments
    cout<<"The number of waiting people is: "<<num_appoint<<endl;
    //average waiting time
    cout<<"The average waiting time is: "<<av_time<<endl;
    //number of withdraw people
    cout<<"The number of withdraw people is: "<< <<endl;
  
    
 cout<<"Monthly Report is done"<<endl;   
    return 0;
}
//------------------------------main function------------------------------
//1. Patients input

//2. Deal with queues and lists

//3. Report: Both weekly and monthly




int main()
{
    int sum_morning_afternoon = 200;
    // Create two local queues.
    // These two local queues per day store 10 people each, i.e., total 20 people a day.
    queue<person*>* localqueue_1;
    queue<person*>* localqueue_2;
    queue<person*>* localqueue_1_medium_risk;
    queue<person*>* localqueue_2_medium_risk;
    queue<person*>* localqueue_1_high_risk;
    queue<person*>* localqueue_2_high_risk;

    Centralized_Queue<person*> Central_queue;
    
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


    
    // Appointment array initialize.
    appointment** appoint_daily;
    appoint_daily = new appointment*[100];
    for(int i=0;i<100;i++){
        appoint_daily[i]=new appointment;
    }
    // Initialize end.


    int k; // This is the morning, afternoon counter.
    int register_process; // This counts what's the index of local register we should process next.
    register_process = 0; // First we should deal with the first register.

    int* register_counter; // Used for monthly report.
    *register_counter = 0;
    int appoint_count=0; // Used for monthly report.
    double time_total=0;
    for( k = 1 ; k <= sum_morning_afternoon ; k++)
    {
        // Main loop here.
        int day = (k + 1) / 2; // Ceiling
        int morning_afternoon = k % 2;
        if(morning_afternoon == 1) // A new day begin
        {  
            int op1,op2;
            cout<<"A new day has begun, Day "<<day<<endl;
            cout<<"Please choose the operation you want:"<<endl;
            cout<<"1.update profession category"<<endl;
            cout<<"2.update risk status"<<endl;
            cout<<"3.withdraw a patient"<<endl;
            cout<<"4.re-register a patient that has withdrawed"<<endl;
            cout<<" Press anything but 1,2,3,4 to continue without any operation"<<endl;
            cin>>op1;
            do
            {
                switch (op1)
                {
                case 1:
                    int new_profession;
                    cout<<"Please enter the ID of the patient"<<endl;
                    cin>>op2;
                    if(typeid(op2) != typeid(int) || op2 <= 0)
                    {
                        cout<<"Please enter the correct id"<<endl;
                        break;
                    }
                    //update profession and change priority
                    cout<<"Please enter the profession you want to change"<<endl;
                    cin>>new_profession;
                    if(typeid(new_profession) != typeid(int) || new_profession <= 0 || new_profession >= 9)
                    {
                        cout<<"Please enter the correct profession number"<<endl;
                        break;
                    }



                    break;
                case 2:
                    int new_risk;
                    cout<<"Please enter the ID of the patient"<<endl;
                    cin>>op2;
                    if(typeid(op2) != typeid(int) || op2 <= 0)
                    {
                        cout<<"Please enter the correct id"<<endl;
                        break;
                    }
                    //update risk status and change priority
                    cin>>new_risk;
                    if(typeid(new_risk) != typeid(int) || new_risk < 0 || new_risk > 3)
                    {
                        cout<<"Please enter the correct risk type"<<endl;
                        break;
                    }
                    break;
                case 3:
                    cout<<"Please enter the ID of the patient"<<endl;
                    cin>>op2;

                    if(typeid(op2) != typeid(int) || op2 <= 0)
                    {
                        cout<<"Please enter the correct id"<<endl;
                        break;
                    }
                    local_register[op2 - 1]->if_withdrawed = true;

                    //withdraw from centralized queue
                    break;
                case 4:
                    cout<<"Please enter the ID of the patient"<<endl;
                    cin>>op2;

                    if(typeid(op2) != typeid(int) || op2 <= 0)
                    {
                        cout<<"Please enter the correct id"<<endl;
                        break;
                    }
                    if( local_register[op2 - 1]->if_withdrawed){
                        
                    }
                default:
                    break;
                }
            }while(op1 == 1 || op1 == 2 || op1 == 3);
        }

        if(morning_afternoon == 1) // Morning
        {
            register_process = local_queue_push_pop(k,register_counter,register_process,local_register,Central_queue,localqueue_1,localqueue_1_medium_risk,localqueue_1_high_risk);
        }
        if(morning_afternoon == 0) // Afternoon
        {
            register_process = local_queue_push_pop(k,register_counter,register_process,local_register,Central_queue,localqueue_2,localqueue_2_medium_risk,localqueue_2_high_risk);
        }
        //laofu
        //**********
        //laofu
        if(morning_afternoon = 0)
        {
            if( day % 30 == 1){
                appoint_count=0;
                time_total=0;
            }
            appointment *today;
            queue<person*> ddl_queue;
            today=appoint_daily[day];
            //how many people have been treated today in total
            int count=0;
            //for every person
                //how many people have deadline today
            int num_ddl=0;
            ddl_queue = Central_queue.fib_heap->pop_ddl(Central_queue.fib_heap->min,day);
            while(!ddl_queue.empty())
            {
                person* ddl_person = ddl_queue.front();
                num_ddl++;
                if(num_ddl<=15){
                    set_appointment(ddl_person,today,day);
                    num_ddl++;
                    today->day_treat[count++]=ddl_person;
                }else{
                    cout<<"the 3 local hospitals today have been fully occupied\n";
                    cout<<"Move the person with deadline today to another hospital in the city town\n";
                }
                ddl_queue.pop();
            }
            int pos_left=today->get_num();
            for(;pos_left>0;pos_left--){
                person *fib=Central_queue.record_out();
                set_appointment(fib,today,day);
                today->day_treat[count++]=fib;
            }
            appoint_count+=(15-today->get_num());
            for(int i=0;i<15;i++){
                person *x =today->day_treat[i];
                time_total+=(x->treated_date-x->register_day);
                int order=x->treated_order;
                switch(order){
                    case 1:
                        x->treated_time="8:00-10:00";
                        break;
                    case 2:
                        x->treated_time="10:00-12:00";
                        break;
                     case 3:
                        x->treated_time="13:00-15:00";
                        break;
                     case 4:
                        x->treated_time="15:00-17:00";
                        break;
                     case 5:
                        x->treated_time="17:00-19:00";
                        break;
                }
            }
            //if not the first day, then we need to update the status of people get treated in previous day
            if(day>1){
                appointment *yesterday;
                yesterday=appoint_daily[day-2];
                for(int j=0;j<15;j++){
                    person *reported=today->day_treat[j];
                    reported->if_treated=true;
                    reported->if_appointed=false;
                    reported->if_queueing=false;
                }
            }
            if ( day % 7 == 0 ){
                cout<<"\n"<<endl;
                cout<<"*******WEEKLY REPORT*******"<<endl;
                report_weekly (day,appoint_daily);
            }
            if ( day % 30 == 0 ){
                cout<<"\n"<<endl;
                cout<<"*******MONTHLY REPORT*******"<<endl;
                double av_time=time_total/30;
                report_monthly (appoint_count,register_counter,av_time);
            }
        }
    }
        








}

    