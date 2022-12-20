// #include<bits/stdc++. h>
#include<iostream>

using namespace std;

//Class process - which will assign values to the data members and print them

class process
{
    int pid,arr_time,brust_time,completion_time, turn_around_time, waiting_time,response_time; 

    public:

    //Constructor to assign values to these data members

    process()
    {
        pid = 0;
        arr_time = 0;
        brust_time = 0;
        completion_time = 0;
        turn_around_time = 0;
        waiting_time = 0;
        response_time = 0;
        cout<<"Process ID : "<<pid<<endl;
        cout<<"Arrival Time : "<<arr_time<<endl;
        cout<<"Brust Time : "<<brust_time<<endl;
        cout<<"Completion Time : "<<completion_time<<endl;
        cout<<"Turn Around Time : "<<turn_around_time<<endl;
        cout<<"Waiting Time : "<<waiting_time<<endl;
        cout<<"Response Time : "<<response_time<<endl;
    }

};

//Class process_creator - which will assign a random arrival time and burst time to each process.

class process_creator
{
    // int pid,arr_time,brust_time,completion_time, turn_around_time, waiting_time,response_time; 


};

// class Schedular - This will implement the scheduling algorithms.

class Schedular
{
    // int pid,arr_time,brust_time,completion_time, turn_around_time, waiting_time,response_time; 


};

// class Simulator - This class will start the simulation.

class Simulator{


};

//First Come First Serve Algorithm
void Fcfs()
{
    cout<<"Enter 1 for First Come First Serve (FCFS) "<<endl;
    
}
void round_robin()
{
    cout<<"Enter 2 for Round Robin Scheduling "<<endl;

}
void cfs()
{
    cout<<"Enter 3 for  Completely Fair Scheduler (CFS) "<<endl;

}

void menu()
{
    cout<<"\n**********************************************************\n"<<endl;
    cout<<"Enter 1 for First Come First Serve (FCFS) "<<endl;
    cout<<"Enter 2 for Round Robin Scheduling "<<endl;
    cout<<"Enter 3 for  Completely Fair Scheduler (CFS) "<<endl;
    cout<<"\n**********************************************************\n"<<endl;
    int choice;
    cin>>choice;
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
        cout<<"\nEnter a valid choice"<<endl;
        menu();
        break;
    }
}

int main()
{
    process p;
    menu();

    
    return 0;
}
