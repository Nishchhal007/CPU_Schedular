// #include<bits/stdc++. h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>

using namespace std;

void starter();
void menu();

// File Handling

void initilize_header_to_status_file();
void initilize_header_to_process_file();

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
    cout << "\n";
    cout << "Process ID : " << pid << endl;
    cout << "Arrival Time : " << arr_time << endl;
    cout << "Brust Time : " << brust_time << endl;
    cout << "Completion Time : " << completion_time << endl;
    cout << "Turn Around Time : " << turn_around_time << endl;
    cout << "Waiting Time : " << waiting_time << endl;
    cout << "Response Time : " << response_time << endl;
    cout << "\n";
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
        a[i].IAB_init(i, at, bt);
    }
    for (int i = 0; i < n; i++)
    {
        a[i].print_details();
    }
}

// class Schedular - This will implement the scheduling algorithms.

// class minHeap()
// {

//     int leftChild(int parent) { return 2 * parent + 1; }
//     int rightChild(int parent) { return 2 * parent + 2; }
//     int parent(int child) { return (child - 1) / 2; }
//     public:

//     void minHeapify(int i)
//     {
//         int l = leftChild(i);
//         int r = rightChild(i);
//         int smallest = i;

//         if (l < arr->size() && arr->at(left).arrivalTime < arr->at(smallest).arrivalTime)
//         {
//             smallest = l;
//         }
//         else
//         {
//             smallest = i;
//         }

//         if (right < arr->size() && arr->at(right).arrivalTime < arr->at(smallest).arrivalTime)
//         {
//             smallest = r;
//         }

//         if (smallest != parent)
//         {
//             swap(arr->at(smallest), arr->at(i));
//             minHeapify(smallest);
//         }
//     }

// }

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

class Simulator
{
private:
    int simulation_time;
    int time_quantum;
    int num_of_processes;
    string schedulingAlgorithm;

public:
    Simulator(int sT, int tQ, int nP, string sA)
    {
        simulation_time = sT;
        time_quantum = tQ;
        num_of_processes = nP;
        schedulingAlgorithm = sA;
    }

    friend class Scheduler;
};

int main()
{
    starter();

    cout << "Enter the No. of Processes : ";
    int num;
    cin >> num;
    int time_quantum;
    int stimulation_time;
    cout << "Enter stimulation time (in secs) : ";
    cin >> stimulation_time;
    string algorithm;
    menu();
    cin >> algorithm;
    int choice;
    cin >> choice;

    // For RR

    if (algorithm.compare("RR"))
    {
        cout << "Enter time Quantum (in ms) : ";
        cin >> time_quantum;
    }

    // Initilizing Headers in status.txt and process.txt

    initilize_header_to_status_file();
    initilize_header_to_process_file();

    return 0;
}

// File handling Functions

void initilize_header_to_status_file()
{
    FILE *fp;
    fp = fopen("status.txt", "w");
    if (fp == NULL)
    {
        printf("Error file opening status.txt !");
        exit(1);
    }
    fprintf(fp, "Milli Seconds(ms)\t\t\tProcess Id\t\t\tStatus\n");
    fclose(fp);
}
void initilize_header_to_process_file()
{
    FILE *fp;
    fp = fopen("process.txt", "w");
    if (fp == NULL)
    {
        printf("Error file opening process.txt !");
        exit(1);
    }
    fprintf(fp, "Process Id\t\tArrival Time\t\tBurst Time\t\tCompletion Time\t\tTurn Around Time\t\tWaiting Time\t\tResponse Time\n");
    fclose(fp);
}

void menu()
{
    cout << "\n**********************************************************\n"
         << endl;
    cout << "FCFS for First Come First Serve (FCFS) " << endl;
    cout << "RR for Round Robin Scheduling " << endl;
    cout << "CFS for Completely Fair Scheduler (CFS) " << endl;
    cout << "\n**********************************************************\n"
         << endl;

}
void starter()
{
    cout << "\n\n\t***************************************************************\n"
         << endl;
    cout << "\t\t\t Welcome to my CPU Schedular " << endl;
    cout << "\n\t***************************************************************\n"
         << endl;
}
