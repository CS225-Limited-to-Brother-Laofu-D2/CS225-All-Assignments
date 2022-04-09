
void appointment::set_num(int num){
    num_left=num;
}

int appointment::get_num(){
    return num_left;
}

void appointment::set_hos(int order,int num){
    each_hos_filled[order-1]=num;
}

int appointment::get_hos(int order){
    return each_hos_filled[order-1];
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

void set_appointment(person *one,appointment *day,int day_now){
    int pos_left=day->get_num();
    if(pos_left==0){
        cout<<"the hospitals have been fully occupied today,try tomorrow!\n";
        return;  
    }
    int best=one->preferred_hos1;
    int good=one->preferred_hos2;
    int fair=one->preferred_hos3;
    one->treated_date=day_now+1;
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

void agesort(int categroy,appointment **appoint_daily,int week, Centralized_Queue<person*> Central_queue, queue<person*>* everyone_loc)
{
    // get the length of the queue p
    int len;
    switch (categroy){
    case 1:
        len=15;
        break;
    case 2:
        len=15*6;
        break;
    case 3:
        len=Central_queue.fib_heap->keyNum;
        break;
    }
    person **temp=new person*[len];
    for(int i=0;i<len;i++){
       temp[i]=new person; 
    }
    // store and pop every element from the queue
    for (int i = 0; i < len; ++i)
    {
        if(categroy==1){
            appointment *temp_appoint=appoint_daily[7*week];
            for(int j=0;j<15;j++){
                temp[i]=temp_appoint->day_treat[j];
            }
        }else if(categroy==2){
            int begin_day=(week-1)*7;
            for(int j=0;j<=5;j++){
                for(int k=0;k<15;k++){
                    appointment *temp_appoint=appoint_daily[begin_day+j];
                    temp[j*15+k]=temp_appoint->day_treat[k];
                }
            }
        }else if(categroy==3){
            int begin=0;
            Central_queue.get_everyone_loc(Central_queue.fib_heap->min, everyone_loc);
            while(!everyone_loc->empty())
            {
                person* one_person= everyone_loc->front();
                temp[begin++]=one_person;
                everyone_loc->pop();
            }
        }
    }

    // use selection sort to sort based on the age
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            person *p1 = temp[max];
            person *p2 = temp[j];

            // if p1 larger than p2, swap them
            if (p1->age_group < p2->age_group)
            {
                max=j;
            }
        }
        person* tmp_tmp = temp[i];
        temp[i] = temp[max];
        temp[max] = tmp_tmp;
    }
    for(int i=0;i<len;i++){
        cout<<"the person with id:"<<temp[i]->id<<"is "<<temp[i]->age<<" years old!\n";
    }
}

void namesort(int categroy,appointment **appoint_daily,int week, Centralized_Queue<person*> Central_queue, queue<person*>* everyone_loc)
{
    // get the length of the queue p
    int len;
    switch (categroy){
    case 1:
        len=15;
        break;
    case 2:
        len=15*6;
        break;
    case 3:
        len=Central_queue.fib_heap->keyNum;
        break;
    }
    person **temp=new person*[len];
    for(int i=0;i<len;i++){
       temp[i]=new person; 
    }
    // store and pop every element from the queue
    for (int i = 0; i < len; ++i)
    {
        if(categroy==1){
            appointment *temp_appoint=appoint_daily[7*week];
            for(int j=0;j<15;j++){
                temp[i]=temp_appoint->day_treat[j];
            }
        }else if(categroy==2){
            int begin_day=(week-1)*7;
            for(int j=0;j<=5;j++){
                for(int k=0;k<15;k++){
                    appointment *temp_appoint=appoint_daily[begin_day+j];
                    temp[j*15+k]=temp_appoint->day_treat[k];
                }
            }
        }else if(categroy==3){
            int begin=0;
            Central_queue.get_everyone_loc(Central_queue.fib_heap->min, everyone_loc);
            while(!everyone_loc->empty())
            {
                person* one_person= everyone_loc->front();
                temp[begin++]=one_person;
                everyone_loc->pop();
            }
        }
    }

    // use selection sort to sort based on the age
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            person *p1 = temp[max];
            person *p2 = temp[j];

            // if p1 larger than p2, swap them
            if (p1->name< p2->name)
            {
                max=j;
            }
        }
        person* tmp_tmp = temp[i];
        temp[i] = temp[max];
        temp[max] = tmp_tmp;
    }
    for(int i=0;i<len;i++){
        cout<<"the person with id:"<<temp[i]->id<<"is name "<<temp[i]->name<<"\n";
    }
}

void profsort(int categroy,appointment **appoint_daily,int week, Centralized_Queue<person*> Central_queue, queue<person*>* everyone_loc)
{
    // get the length of the queue p
    int len;
    switch (categroy){
    case 1:
        len=15;
        break;
    case 2:
        len=15*6;
        break;
    case 3:
        len=Central_queue.fib_heap->keyNum;
        break;
    }
    person **temp=new person*[len];
    for(int i=0;i<len;i++){
       temp[i]=new person; 
    }
    // store and pop every element from the queue
    for (int i = 0; i < len; ++i)
    {
        if(categroy==1){
            appointment *temp_appoint=appoint_daily[7*week];
            for(int j=0;j<15;j++){
                temp[i]=temp_appoint->day_treat[j];
            }
        }else if(categroy==2){
            int begin_day=(week-1)*7;
            for(int j=0;j<=5;j++){
                for(int k=0;k<15;k++){
                    appointment *temp_appoint=appoint_daily[begin_day+j];
                    temp[j*15+k]=temp_appoint->day_treat[k];
                }
            }
        }else if(categroy==3){
            int begin=0;
            Central_queue.get_everyone_loc(Central_queue.fib_heap->min, everyone_loc);
            while(!everyone_loc->empty())
            {
                person* one_person= everyone_loc->front();
                temp[begin++]=one_person;
                everyone_loc->pop();
            }
        }
    }

    // use selection sort to sort based on the age
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            person *p1 = temp[max];
            person *p2 = temp[j];

            // if p1 larger than p2, swap them
            if (p1->profession < p2->profession)
            {
                max=j;
            }
        }
        person* tmp_tmp = temp[i];
        temp[i] = temp[max];
        temp[max] = tmp_tmp;
    }
    for(int i=0;i<len;i++){
        cout<<"the person with id:"<<temp[i]->id<<"is in profession category"<<temp[i]->profession<<"\n";
    }
}

