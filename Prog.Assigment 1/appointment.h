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
    int get_hos_1();
    int get_hos_2();
    int get_hos_3();
    int get_num();
    void set_hos_1(int num);
    void set_hos_2(int num);
    void set_hos_3(int num);
    void set_num(int num);
private:
    //how many people has been filled for each day
    int hospital_1;
    int hospital_2;
    int hospital_3;
    //how many positions in 3 hospitals are still left
    int num_left;
};

appointment::appointment(/* args */)
{
    set_hos_1(0);
    set_hos_2(0);
    set_hos_3(0);
    set_num(9);
}

#endif
