// #include<bits/stdc++. h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>

using namespace std;

#define n1 100

// Queue Functions

class Queue
{
    int *arr;
    int front;
    int back;

public:
    Queue()
    {
        arr = new int[n1];
        front = -1;
        back = -1;
    }
    void enqueue(int x);
    void dequeue();
    int peak();
    bool isEmpty();
};

void Queue ::enqueue(int x)
{
    if (back == n1 - 1)
    {
        cout << "Queue Overflow" << endl;
    }
    back++;
    arr[back] = x;
    if (front == -1)
    {
        front++;
        arr[front] = x;
    }
}
void Queue ::dequeue()
{
    if (front == -1 || front > back)
    {
        cout << "No element in Queue" << endl;
        return;
    }
    front++;
}
int Queue ::peak()
{

    if (front == -1 || front > back)
    {
        cout << "No Element in Queue";
        return -1;
    }
    return arr[front];
}

bool Queue ::isEmpty()
{
    if (front == -1 || front > back)
    {
        return true;
    }
    return false;
}

// Starter menu Functions

void starter();
void menu();

// File Handling Function

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
        completion_time = 0;
    }
    void print_details();
    void response(int t);
    void completion(float completion_time);
    void IAB_init(int id, int at, int bt);
    friend class minHeap;
};

void process::IAB_init(int id, int at, int bt)
{
    pid = id;
    arr_time = at;
    brust_time = bt;
}
void process::completion(float completion_time = 0)
{
    this->completion_time = completion_time;
    turn_around_time = completion_time - arr_time;
    waiting_time = turn_around_time - brust_time;
}

void process::response(int t)
{
    if (response_time == -1)
        response_time = t - arr_time;
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
        bt = 1 + rand() % 10;
        a[i].IAB_init(i, at, bt);
    }
    for (int i = 0; i < n; i++)
    {
        a[i].print_details();
    }
}

// Min Heap

class minHeap
{
private:
    
    process *a = new process[10];
    
    int left(int i)
    {
        return 2 * i + 1;
    }
    int right(int i)
    {
        return 2 * i + 2;
    }
    int parent(int i)
    {
        return (i - 1) / 2;
    }

    void min_heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < sizeof(a) && a[l].arr_time < a[smallest].arr_time)
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }

        if (r < sizeof(a) && a[r].arr_time < a[smallest].arr_time)
        {
            smallest = r;
        }

        if (smallest != i)
        {
            swap(a[smallest], a[i]);
            min_heapify(smallest);
        }
    }

public:
    minHeap(process *arr)
    {
        a = arr;
        build_min_heap();
    }

    void build_min_heap();
    process get_min_ele();
    void pop();
};

void minHeap::build_min_heap()
{
    for (int i = (sizeof(a) / 2) - 1; i >= 0; i--)
    {
        min_heapify(i);
    }
}

process minHeap::get_min_ele()
{
    return a[0];
}

void minHeap::pop()
{
    int x = sizeof(a);
    a[0] = a[x - 1];
    x = x - 1;
    min_heapify(0);
}

// class Schedular - This will implement the scheduling algorithms.

class Schedular
{
    process *ready_queue[999999];

public:
    void schedule_processes(process_creator &PC, int simulation_time, int time_quantum, string sAlgorithm)
    {
        // string fa = "FCFS";
        // string sa = "RR";
        // string ta = "CFS";
        if (sAlgorithm == "FCFS")
        {
            // Schedular_FCFS Fcfs(PC);
            // for (int i = 1; i <= simulationTime; i++)
            // {
            //     cout << "\nIteration is " << i << endl;
            //     Fcfs.FCFS(PC, i);
            // }
            // while (Fcfs.readyQueue.empty() == false)
            // {
            //     // Process P = Fcfs.readyQueue.top();
            //     // writeDataToProcessesFile(P.Data);
            //     Fcfs.readyQueue.pop();
            // }
            // return;
        }
    }
};

// Class for implementation of FCFS Schedular

class Schedular_FCFS
{
};

class Simulator
{
private:
    int simulation_time;
    int time_quantum;
    int num_of_processes;
    string sAlgorithm;

public:
    Simulator(int sT, int tQ, int n, string sA)
    {
        simulation_time = sT;
        time_quantum = tQ;
        num_of_processes = n;
        sAlgorithm = sA;
    }
    void init_simulation()
    {
        // process_creator PC(num_of_processes);
        process_creator pc;
        pc.Assign(num_of_processes);
        Schedular s;
        s.schedule_processes(pc, simulation_time, time_quantum, sAlgorithm);
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
    int simulation_time;
    cout << "Enter stimulation time (in secs) : ";
    cin >> simulation_time;
    string salgorithm;
    menu();
    cin >> salgorithm;

    // For RR

    if (salgorithm.compare("RR") == 0)
    {
        cout << "Enter time Quantum (in ms) : ";
        cin >> time_quantum;
    }

    // Initilizing Headers in status.txt and process.txt

    initilize_header_to_status_file();
    initilize_header_to_process_file();

    // Start Simulation

    Simulator Simulation(simulation_time, time_quantum, num, salgorithm);
    Simulation.init_simulation();

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
