#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

#define num 20
#define MAX_SIZE 999999

using namespace std;

void starter();
void menu();

// // Class Queue and its Functions

// class Queue
// {
//     Process **arr;
//     int front;
//     int back;
//     int size;

// public:
//     Queue()
//     {
//         arr = new Process *[MAX_SIZE];
//         front = 0;
//         back = -1;
//         size = 0;
//     };
//     void enqueue(Process x)
//     {
//         if (size == MAX_SIZE)
//         {
//             cout << "Error: Queue is full" << endl;
//             return;
//         }
//         back = (back + 1) % MAX_SIZE;
//         *arr[back] = x;
//         size++;
//     }
//     void dequeue()
//     {
//         if (size == 0)
//         {
//             cout << "Error: Queue is empty" << endl;
//             return;
//         }
//         front = (front + 1) % MAX_SIZE;
//         size--;
//     }
//     Process peak()
//     {
//         if (size == 0)
//         {
//             cout << "Error: Queue is empty" << endl;
//             exit(1);
//         }
//         return *arr[front];
//     }
//     Process back_ele()
//     {
//         if (size == 0)
//         {
//             cout << "Error: Queue is empty" << endl;
//             exit(1);
//         }
//         return *arr[back];
//     }
//     int Size() { return size; }
//     bool isEmpty()
//     {
//         if (front == -1 || front > back)
//         {
//             return true;
//         }
//         return false;
//     }
//     friend class Process;
//     friend class Scheduler;
//     friend class Simulator;
//     friend class Schedular_FCFS;
// };

class process_details
{
    int pid;
    int arr_time;
    int brust_time;
    int init_brust_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;

public:
    friend void print_basic_process_info(process_details processes_data);
    friend void print_process_details(process_details processes_data);
    friend void write_update_to_status_file(process_details PD, const char status[], int t);
    friend void write_update_to_process_file(process_details PD);

    friend class Process;
    friend class Process_Creator;
    friend class minHeap;
    friend class Queue;
    friend class Scheduler;
    friend class Scheduler_FCFS;
    friend class Scheduler_RR;
};

class Process
{
    process_details processes_data;

public:
    // Constructor for Process for assigning values

    Process(process_details pd)
    {
        processes_data.pid = pd.pid;
        processes_data.arr_time = pd.arr_time;
        processes_data.brust_time = pd.brust_time;
        processes_data.init_brust_time = pd.init_brust_time;
        processes_data.completion_time = pd.completion_time;
        processes_data.turn_around_time = pd.turn_around_time;
        processes_data.waiting_time = pd.waiting_time;
        processes_data.response_time = pd.response_time;
    }
    // Function For assigning Values

    void assign_process_details(process_details pd)
    {
        processes_data.pid = pd.pid;
        processes_data.arr_time = pd.arr_time;
        processes_data.brust_time = pd.brust_time;
        processes_data.init_brust_time = pd.init_brust_time;
        processes_data.completion_time = pd.completion_time;
        processes_data.turn_around_time = pd.turn_around_time;
        processes_data.waiting_time = pd.waiting_time;
        processes_data.response_time = pd.response_time;
    }
    int get_pid()
    {
        return processes_data.pid;
    }
    int get_at()
    {
        return processes_data.arr_time;
    }
    int get_bt()
    {
        return processes_data.init_brust_time;
    }
    friend void print_process_details(process_details processes_data);
    friend void print_basic_process_info(process_details processes_data);
    friend class Process_Creator;
    friend class minHeap;
    friend class Queue;
    friend class Scheduler;
    friend class Scheduler_FCFS;
    friend class Scheduler_RR;
};

void print_process_details(process_details processes_data)
{

    cout << "\n";
    cout << "Process ID : " << processes_data.pid << endl;
    cout << "Arrival Time : " << processes_data.arr_time << endl;
    cout << "Brust Time : " << processes_data.init_brust_time << endl;
    cout << "Completion Time : " << processes_data.completion_time << endl;
    cout << "Turn Around Time : " << processes_data.turn_around_time << endl;
    cout << "Waiting Time : " << processes_data.waiting_time << endl;
    cout << "Response Time : " << processes_data.response_time << endl;
    cout << "\n";
}
void print_basic_process_info(process_details processes_data)
{
    cout << "Process ID : " << processes_data.pid
         << "\tArrival Time : " << processes_data.arr_time
         << "\tBrust Time : " << processes_data.brust_time << endl;
}

class Process_Creator
{

    // Array of Processes
    Process **processes;

public:
    Process_Creator()
    {
        process_details pd;

        pd.completion_time = -1;
        pd.turn_around_time = -1;
        pd.waiting_time = -1;
        pd.response_time = -1;

        // Allocates Memory for the Array

        processes = new Process *[num];

        // Initializing the arrival time and burst time with Random Values

        cout << "\n\t\tProcess Info\t\t\n"
             << endl;
        for (int i = 0; i < num; i++)
        {
            pd.pid = i;
            pd.arr_time = rand() % 10;
            pd.brust_time = 1 + rand() % 10;
            pd.init_brust_time = pd.brust_time;
            // Storing diff Process index wise in each index of processes Array
            processes[i] = new Process(pd);
            print_basic_process_info(processes[i]->processes_data);
        }
    }
    friend void print_process_details(process_details processes_data);
    friend void print_basic_process_info(process_details processes_data);
    friend void set_brust_time(int x);
    friend class minHeap;
    friend class Queue;
    friend class Scheduler;
    friend class Scheduler_FCFS;
    friend class Scheduler_RR;
};

class Compare
{
public:
    int operator()(Process &p1, Process &p2)
    {
        if (p1.get_at() == p2.get_at())
        {
            return p1.get_pid() > p2.get_pid();
        }
        return p1.get_at() > p2.get_at();
    }
};

class Scheduler_FCFS
{
    priority_queue<Process, vector<Process>, Compare> ready_queue;

public:
    Scheduler_FCFS(Process_Creator &PC)
    {
        // Constructor of the Class
    }
    void check_process_arrival_FCFS(Process_Creator &pc, int t)
    {
        for (int i = 0; i < num; i++)
        {
            if (pc.processes[i]->processes_data.arr_time == t)
            {
                ready_queue.push(Process(pc.processes[i]->processes_data));
                write_update_to_status_file(pc.processes[i]->processes_data, "Arrived", t);
                cout << "t and AT Matched" << pc.processes[i]->processes_data.arr_time << endl;
            }
        }
    }
    void write_to_status_file(const char status[], int t)
    {
        Process P = ready_queue.top();
        write_update_to_status_file(P.processes_data, status, t);
        return;
    }

    void write_to_processes_file(process_details process_data)
    {
        write_update_to_process_file(process_data);
    }

    void FCFS(Process_Creator &PC, int t)
    {
        check_process_arrival_FCFS(PC, t);
        if (ready_queue.empty() == false)
        {
            Process P = ready_queue.top();
            if (P.processes_data.brust_time != 0)
            {
                write_to_status_file("Running", t);
                P.processes_data.brust_time -= 1;
                if (P.processes_data.response_time == -1)
                {
                    P.processes_data.response_time = t - P.processes_data.arr_time;
                }
                ready_queue.pop();
                ready_queue.push(Process(P.processes_data));
            }
            else
            {
                write_to_status_file("Exit", t);
                P.processes_data.completion_time = t;
                P.processes_data.turn_around_time = P.processes_data.completion_time - P.processes_data.arr_time;
                P.processes_data.waiting_time = P.processes_data.turn_around_time - P.processes_data.brust_time;
                write_to_processes_file(P.processes_data);
                ready_queue.pop();
                if (ready_queue.empty() == false)
                {
                    P = ready_queue.top();
                    P.processes_data.brust_time -= 1;
                    write_to_status_file("Running", t);
                    if (P.processes_data.response_time == -1)
                    {
                        P.processes_data.response_time = t - P.processes_data.arr_time;
                    }
                    ready_queue.pop();
                    ready_queue.push(Process(P.processes_data));
                }
                printf("\nProcess Completed...\n");
            }
            // P.print_process_details();
        }
    }
    friend class Scheduler;
};

class Scheduler_RR
{
    // Min Heap ready Queue
    priority_queue<Process, vector<Process>, Compare> ready_queue;
    priority_queue<Process, vector<Process>, Compare> running_queue;
    int index, time_quantum;

public:
public:
    Scheduler_RR(Process_Creator &PC, int tq)
    {
        // Constructor of The Class

        index = 0;
        time_quantum = tq;
    }
    void check_arrival_rr(Process_Creator &PC, int t)
    {
        for (int i = 0; i < num; i++)
        {
            if (PC.processes[i]->processes_data.arr_time == t)
            {
                ready_queue.push(Process(PC.processes[i]->processes_data));
                write_update_to_status_file(PC.processes[i]->processes_data, "Arrived", t);
                cout << "t and AT Matched" << PC.processes[i]->processes_data.arr_time << endl;
            }
        }
    }
    void write_to_status_file(const char status[], int t)
    {
        Process P = running_queue.top();
        write_update_to_status_file(P.processes_data, status, t);
        return;
    }
    void write_to_processes_file(process_details pd)
    {
        write_update_to_process_file(pd);
    }
    // readyQueue1 - ready_queue
    // readyQueue - running_queue
    void Round_Robin(Process_Creator PC, int t)
    {
        check_arrival_rr(PC, t);
        if (running_queue.empty() == true && ready_queue.empty() == false)
        {
            while (ready_queue.empty() == false)
            {
                Process P = ready_queue.top();
                ready_queue.pop();
                running_queue.push(Process(P.processes_data));
            }
        }
        if (running_queue.empty() == false)
        {
            if (index == time_quantum)
            {
                index = 0;
                Process P = running_queue.top();
                running_queue.pop();
                ready_queue.push(Process(P.processes_data));
                if (running_queue.empty() == true && ready_queue.empty() == false)
                {
                    while (ready_queue.empty() == false)
                    {
                        Process P = ready_queue.top();
                        ready_queue.pop();
                        running_queue.push(Process(P.processes_data));
                    }
                }
            }
            index = index + 1;
            Process P = running_queue.top();
            if (P.processes_data.brust_time != 0)
            {
                write_to_status_file("Running", t);
                P.processes_data.brust_time -= 1;
                if (P.processes_data.response_time == -1)
                {
                    P.processes_data.response_time = t - P.processes_data.arr_time;
                }
                running_queue.pop();
                running_queue.push(Process(P.processes_data));
            }
            else
            {
                write_to_status_file("Exit", t);
                P.processes_data.completion_time = t;
                P.processes_data.turn_around_time = P.processes_data.completion_time - P.processes_data.arr_time;
                P.processes_data.waiting_time = P.processes_data.turn_around_time - P.processes_data.init_brust_time;
                write_to_processes_file(P.processes_data);
                running_queue.pop();
                if (running_queue.empty() == false)
                {
                    P = running_queue.top();
                    write_to_status_file("Running", t);
                    P.processes_data.brust_time -= 1;
                    if (P.processes_data.response_time == -1)
                    {
                        P.processes_data.response_time = t - P.processes_data.arr_time;
                    }
                    running_queue.pop();
                    running_queue.push(Process(P.processes_data));
                }
                printf("\nProcess Completed...\n");
            }
        }
    }
    friend class Scheduler;
};

class Scheduler
{
    priority_queue<Process, vector<Process>, Compare> ready_queue;

public:
    void schedule_process(Process_Creator &PC, int simulation_time, int time_quantum, int choice)
    {
        if (choice == 1)
        {
            Scheduler_FCFS Fcfs(PC);
            for (int i = 1; i <= simulation_time; i++)
            {
                cout << "\nIteration is " << i << endl;
                Fcfs.FCFS(PC, i);
            }
            while (Fcfs.ready_queue.empty() == false)
            {
                Process P = Fcfs.ready_queue.top();
                write_update_to_process_file(P.processes_data);
                Fcfs.ready_queue.pop();
            }
            return;
        }
        else if (choice==2)
        {
            Scheduler_RR rr(PC, time_quantum);
            for (int i = 1; i <= simulation_time; i++)
            {
                cout << "\nIteration is " << i << endl;
                rr.Round_Robin(PC, i);
            }
            while (rr.ready_queue.empty() == false)
            {
                Process P = rr.ready_queue.top();
                write_update_to_process_file(P.processes_data);
                rr.ready_queue.pop();
            }
            return;
            
        }
        
        else
        {
            // Scheduler_CFS cfs();
        }
    }
};

class Simulator
{
    int simulation_time;
    int time_quantum;
    int num_of_processes;
    int choice;

public:
    Simulator(int st, int tq, int x)
    {
        simulation_time = st;
        time_quantum = tq;
        choice = x;
    }

    void init_simulation()
    {
        Process_Creator pc;
        Scheduler s;
        s.schedule_process(pc, simulation_time, time_quantum, choice);
    }
    friend class Scheduler;
};

// Min Heap

class minHeap
{
private:
    Process *a;

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

        if (l < sizeof(a) && a[l].processes_data.arr_time < a[smallest].processes_data.arr_time)
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }

        if (r < sizeof(a) && a[r].processes_data.arr_time < a[smallest].processes_data.arr_time)
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
    minHeap(Process *arr)
    {
        a = arr;
        build_min_heap();
    }

    void build_min_heap();
    Process get_min_ele();
    void rem_back_ele();
};

void minHeap::build_min_heap()
{
    for (int i = (sizeof(a) / 2) - 1; i >= 0; i--)
    {
        min_heapify(i);
    }
}

Process minHeap::get_min_ele()
{
    return a[0];
}

void minHeap::rem_back_ele()
{
    int x = sizeof(a);
    a[0] = a[x - 1];
    x = x - 1;
    min_heapify(0);
}

// File Handling Functions.

void initilize_header_to_status_file();
void initilize_header_to_process_file();
void write_update_to_status_file(process_details PD, const char status[], int t);
void write_update_to_process_file(process_details PD);

int main()
{
    starter();

    int simulation_time;

    int time_quantum;
    cout << "Enter stimulation time (in milli-seconds) : ";
    cin >> simulation_time;

    // // Converting stimulation time into mili-Seconds

    // simulation_time = simulation_time * 1000;
    int choice;
    menu();
    cin >> choice;

    // For RR

    if (choice == 2)
    {
        cout << "Enter time Quantum (in ms) : ";
        cin >> time_quantum;
    }

    // Writing Headers in status.txt and process.txt

    initilize_header_to_status_file();
    initilize_header_to_process_file();

    // Start Simulation

    Simulator Simulation(simulation_time, time_quantum, choice);
    Simulation.init_simulation();

    return 0;
}

void menu()
{
    cout << "\n**********************************************************\n"
         << endl;
    cout << "Enter 1 for First Come First Serve (FCFS) " << endl;
    cout << "Enter 2 for Round Robin Scheduling(RR) " << endl;
    cout << "Enter 3 for Completely Fair Scheduler (CFS) " << endl;
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

void write_update_to_status_file(process_details PD, const char status[], int t)
{
    FILE *fp;
    fp = fopen("status.txt", "a");
    if (fp == NULL)
    {
        printf("\nError file Updating... status.txt !\n");
    }
    fprintf(fp, "%17d\t\t\t%10d\t\t\t%s\n", t, PD.pid, status);
    fclose(fp);
}

void write_update_to_process_file(process_details PD)
{
    FILE *fp;
    fp = fopen("process.txt", "a");
    if (fp == NULL)
    {
        printf("\nError file Updating... process.txt !\n");
    }
    fprintf(fp, "%10d\t\t%12d\t\t%10d\t\t%15d\t\t%16d\t\t%12d\t\t%13d\n", PD.pid, PD.arr_time, PD.init_brust_time, PD.completion_time, PD.turn_around_time, PD.waiting_time, PD.response_time);
    fclose(fp);
}