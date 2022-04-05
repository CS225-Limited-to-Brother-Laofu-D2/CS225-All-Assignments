//CA1 Group D2

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <queue>
using std::cout;
using std::cin;

#include "Register.h"

using namespace std;
//Include.h files and other .cpp files here

//weekly report:Treated people；Registered people with appointment；Queueing people without appointments
//(Including prof+age+risk+time)
int report_weekly (int)
{
    return 0;
}
//monthly report:Number of registered people; Number of waiting people (already in register); Number of appointments

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

    person** local_register;
    local_register = new person*[500];

    // File open
    ifstream registry1("registry_1.csv", ios::in);
    if (!registry1)
    {
        cout << "Cannot open registry_1, program terminated." << endl;
        return 0;
    }
 
    registry1

}