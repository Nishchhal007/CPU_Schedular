// #include<bits/stdc++. h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void menu();

// Class process - which will assign values to the data members and print them

class process
{
    int pid, arr_time, brust_time, completion_time, turn_around_time, waiting_time, response_time;

public:
    // Constructor to initilize values to these data members

    process()
    {
        pid = 0;
        arr_time = 0;
        brust_time = 0;
        completion_time = 0;
        turn_around_time = 0;
        waiting_time = 0;
        response_time = 0;
    }
    void print_details();
    void IAB_init(int id, int at, int bt);
};


void process::IAB_init(int id, int at, int bt)
{
    pid = id;
    arr_time = at;
    brust_time = bt;
}
void process::print_details()
{
        cout<<"\n";
        cout<<"Process ID : "<<pid<<endl;
        cout<<"Arrival Time : "<<arr_time<<endl;
        cout<<"Brust Time : "<<brust_time<<endl;
        cout<<"Completion Time : "<<completion_time<<endl;
        cout<<"Turn Around Time : "<<turn_around_time<<endl;
        cout<<"Waiting Time : "<<waiting_time<<endl;
        cout<<"Response Time : "<<response_time<<endl;
        cout<<"\n";
}


// Class process_creator - which will assign a random arrival time and burst time to each process.


class process_creator
{
    int at;
    int bt;

public:
    // Function for Assigning Random Time for arrival_time,Brust_time
    void Assign(int n);
};

void process_creator ::Assign(int n)
{
    process *a = new process[n];
    for (int i = 0; i < n; i++)
    {
        at = rand() % 10;
        bt = rand() % 10 + 1;
        a[i].IAB_init(i,at,bt);
    }
    for (int i = 0; i < n; i++)
    {
        a[i].print_details();
    }
    
}

// class Schedular - This will implement the scheduling algorithms.

class Schedular //:: public process_creator
{

public:
    friend void Fcfs();
    friend void round_robin();
    friend void cfs();
};
void Fcfs()
{
}
void round_robin()
{
    cout << "Enter 2 for Round Robin Scheduling " << endl;
}
void cfs()
{
    cout << "Enter 3 for  Completely Fair Scheduler (CFS) " << endl;
}

int main()
{

    menu();
    int num;
    cout << "Enter the No. of Processes : ";
    cin >> num;
    process_creator new_process;
    new_process.Assign(num);
    // print_details();

    return 0;
}

void menu()
{
    cout << "\n**********************************************************\n"
         << endl;
    cout << "Enter 1 for First Come First Serve (FCFS) " << endl;
    cout << "Enter 2 for Round Robin Scheduling " << endl;
    cout << "Enter 3 for Completely Fair Scheduler (CFS) " << endl;
    cout << "\n**********************************************************\n"
         << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        Fcfs();
        break;
    case 2:
        round_robin();
        break;
    case 3:
        cfs();
        break;

    default:
        cout << "\nEnter a valid choice ! Try Again" << endl;
        menu();
        break;
    }
}


