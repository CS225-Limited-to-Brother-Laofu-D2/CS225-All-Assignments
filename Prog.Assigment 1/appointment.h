//
// appointment.h Created by Group D2
// 2022.04.05
//
#ifndef appointment_h
#define appoointment_h
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
#include"Register.h"

class appointment
{
public:
    appointment(/* args */);
    int get_hos(int order);
    int get_num();
    void set_hos(int order,int num);
    void set_num(int num);
private:
    //how many people has been filled for each day
    int *each_hos_filled;
    //how many positions in 3 hospitals are still left
    int num_left;
};

#endif
