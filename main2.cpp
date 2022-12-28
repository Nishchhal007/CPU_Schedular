// #include<bits/stdc++. h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<vector>
#include <algorithm>
#include <utility>

#define n 7

using namespace std;



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
        cout << "Process ID : " << pid << endl;
        cout << "Arrival Time : " << arr_time << endl;
        cout << "Brust Time : " << brust_time << endl;
        cout << "Completion Time : " << completion_time << endl;
        cout << "Turn Around Time : " << turn_around_time << endl;
        cout << "Waiting Time : " << waiting_time << endl;
        cout << "Response Time : " << response_time << endl;
    }

    // Constructor overloaded for assigning Values

    // process(int id = 0,int at= 0,int bt= 0,int ct= 0,int tat= 0,int wt= 0,int rt= 0)
    // {
    //     pid = id;
    //     arr_time = at;
    //     brust_time = bt;
    //     completion_time = ct;
    //     turn_around_time = tat;
    //     waiting_time = wt;
    //     response_time = rt;
    //     cout<<"Process ID : "<<pid<<endl;
    //     cout<<"Arrival Time : "<<arr_time<<endl;
    //     cout<<"Brust Time : "<<brust_time<<endl;
    //     cout<<"Completion Time : "<<completion_time<<endl;
    //     cout<<"Turn Around Time : "<<turn_around_time<<endl;
    //     cout<<"Waiting Time : "<<waiting_time<<endl;
    //     cout<<"Response Time : "<<response_time<<endl;

    // }
};

// Class process_creator - which will assign a random arrival time and burst time to each process.

class Process
{
public:
    int arrival_time;
    int burst_time;
    int Priority;
};

Process a[n];

class process_creator
{

public:
    // Function for Assigning Random Time for arrival_time,Brust_time

    void Assign(int x);
    friend void Fcfs(Process a[n]);
};

void process_creator ::Assign(int x)
{
    Process a[n];
    for (int i = 0; i < x; i++)
    {
        a[i].arrival_time = rand() % 10;
        a[i].burst_time = rand() % 10+1;
    }

    // Print the processes
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << ": arrival time = " << a[i].arrival_time << ", burst time = " << a[i].burst_time << endl;
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

// class Simulator - This class will start the simulation.

class Simulator
{
};

// First Come First Serve Algorithm
void Fcfs(Process a[n])
{

  // Define a vector to store the indices of the elements of the array
  vector<pair<int, int>> indices;
  for (int i = 0; i < n; i++) {
    indices.emplace_back(a[i].arrival_time, i);
  }

  // Sort the vector of indices based on the value of the elements of the array
  sort(indices.begin(), indices.end(), [](auto a, auto b) {
    return a.first < b.first;
  });

  // Print the sorted array and the indices of the elements
  for (const auto& [value, index] : indices) {
    cout << value << ' ' << index << '\n';
  }


}
void round_robin()
{
    cout << "Enter 2 for Round Robin Scheduling " << endl;
}
void cfs()
{
    cout << "Enter 3 for  Completely Fair Scheduler (CFS) " << endl;
}

void menu()
{
    cout << "\n**********************************************************\n"
         << endl;
    cout << "Enter 1 for First Come First Serve (FCFS) " << endl;
    cout << "Enter 2 for Round Robin Scheduling " << endl;
    cout << "Enter 3 for  Completely Fair Scheduler (CFS) " << endl;
    cout << "\n**********************************************************\n"
         << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        Fcfs(a[]);
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

int main()
{
    process p;
    menu();
    process_creator pc;
    pc.Assign(n);

    return 0;
}
