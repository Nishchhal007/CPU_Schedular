#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>
#include <iostream>

#define num 8
#define MAX_SIZE 999999
#define size 100

using namespace std;

// Starter menu Functions

void starter();
void menu();

class process_details
{
    int pid;
    int arr_time;
    int brust_time;
    int init_brust_time;
    int completion_time;
    int executed;
    int rem_brust_time;
    int turn_around_time;
    int waiting_time;
    int response_time;

public:
    friend void print_basic_process_info(process_details processes_data);
    friend void print_process_details(process_details processes_data);
    friend void update_status_file(int pid, const char status[], int t);
    friend void update_process_file(process_details PD);

    friend class Process;
    friend class Process_Creator;
    friend class Scheduler;
    friend class implement_algo;
    friend class Scheduler_RR;
};

class Process
{
    process_details processes_data;

public:
    Process()
    {

        // Constructor for Process
    }
    Process(process_details pd)
    {
        processes_data.pid = pd.pid;
        processes_data.arr_time = pd.arr_time;
        processes_data.brust_time = pd.brust_time;
        processes_data.init_brust_time = pd.init_brust_time;
        processes_data.rem_brust_time = pd.rem_brust_time;
        processes_data.executed = pd.executed;
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
        processes_data.rem_brust_time = pd.rem_brust_time;
        processes_data.executed = pd.executed;
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
    void completion(float completion_time = 0)
    {
        this->processes_data.completion_time = processes_data.completion_time;
        processes_data.turn_around_time = processes_data.completion_time - processes_data.arr_time;
        processes_data.waiting_time = processes_data.turn_around_time - processes_data.brust_time;
    }

    void response(int t)
    {
        if (processes_data.response_time == -1)
        {
            processes_data.response_time = t - processes_data.arr_time;
        }
    }
    friend void print_process_details(process_details processes_data);
    friend void print_basic_process_info(process_details processes_data);
    friend class Process_Creator;
    friend class Scheduler;
    friend class implement_algo;
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
        pd.executed = -1;

        // Allocates Memory for the Array

        processes = new Process *[num];

        // Initializing the arrival time and burst time with Random Values

        cout << "\n\t\tProcesses Info\t\t\n"
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
    friend class Scheduler;
    friend class implement_algo;
    friend class Scheduler_RR;
};

// File Handling Functions.

void init_status();
void init_process();
void update_status_file(int pid, const char status[], int t);
void update_process_file(process_details PD);

class implement_algo
{
    int queue[size] = {0};       // running queue for the simulator .stores the process ids.
    int ready_queue[size] = {0}; // to store the processes id which are ready to get executed at the given point of time
    int ready_queue_top = -1;    // index to indicate the top element of ready_queue .just liready_queue_tope top in queue.
    int queue_top;               // index to the top element in queue
    int init_time = -1;          // used to store the time the running process started its execution
    int min_burst = INT_MAX;     // to store the minimum burst time required in STRF nad round robin
    int min_burst_index = -1;    // to store the index of minimum burst time process present in the ready_queue
public:
    implement_algo(Process_Creator PC)
    {
        queue_top = -1;
    }

    bool enqueue(Process_Creator PC, int pId, int t)
    {
        if (queue_top == size - 1)
        {

            return false;
        }
        else
        {
            // cout << "enqueued" << endl;
            queue_top++;
            queue[queue_top] = pId;
            if (queue_top == 0)
            {
                init_time = t;
                int update_id = PC.processes[queue[0]]->processes_data.pid;
                update_status_file(update_id, "running", t);
                // out.open("status.txt", ios_base::app);
                // out << setw(15) << t;
                // out << setw(15) << processes.arr[queue[0]].pId;
                // out << setw(15) << "arrived";
                // out << endl;
                // out.close();
                Process *P = PC.processes[queue[0]];
                P->response(t);
                // processes.arr[queue[0]].response(t);
            }
            return true;
        }
    }

    bool dequeue(Process_Creator PC, int t)
    {
        if (queue_top == -1)
            return false;
        else
        {
            // cout << "dequeued" << endl;

            int p_executed = queue[0];
            Process *P = PC.processes[queue[0]];
            P->completion(t);
            // PC.processes[queue[0]].processes_data.completion(t);
            init_time = t;
            for (int i = 0; i < queue_top; i++)
            {
                queue[i] = queue[i + 1];
            }
            queue[queue_top] = 0;
            queue_top--;
            int update_id = PC.processes[p_executed]->processes_data.pid;
            update_status_file(update_id, "exit", t);
            // out.open("status.txt", ios_base::app);
            // out << setw(15) << t;
            // out << setw(15) << processes.arr[p_executed].pId;
            // out << setw(15) << "exit";
            // out << endl;
            if (queue_top != -1)
            {
                update_status_file(update_id, "arrived", t);
                // out << setw(15) << t;
                // out << setw(15) << processes.arr[queue[0]].pId;
                // out << setw(15) << "arrived";
                // out << endl;
                // out.close();
                // processes.arr[queue[0]].response(t);
                Process *P = PC.processes[queue[0]];
                P->response(t);
            }
            PC.processes[p_executed]->processes_data.executed = -1;
            // processes.arr[p_executed].executed = -1;
            return true;
        }
    }

    int FCFS(Process_Creator PC, int t)
    {
        cout << t << " millisec" << endl;
        for (int i = 0; i < size; i++)
        {
            // processes.arr[i]. - PC.processes[i]->processes_data

            if (PC.processes[i]->processes_data.executed != -1 && PC.processes[i]->processes_data.arr_time == t)
            {
                ready_queue_top++;
                ready_queue[ready_queue_top] = PC.processes[i]->processes_data.pid;
            }
        }

        if (ready_queue_top != -1 && t - init_time == PC.processes[queue[0]]->processes_data.brust_time)
        {
            if (dequeue(PC, t) == 0)
            {
            }
        }
        else if (ready_queue_top != -1)
        {
            int update_id = PC.processes[queue[0]]->processes_data.pid;
            update_status_file(update_id, "running", t);
            // out.open("status.txt", ios_base::app);
            // out << setw(15) << t;
            // out << setw(15) << processes.arr[queue[0]].pId;
            // out << setw(15) << "running";
            // out << endl;
            // out.close();
        }
        if (ready_queue_top != -1 && enqueue(PC, ready_queue[0], t))
        {
            for (int j = 0; j < ready_queue_top; j++)
            {
                ready_queue[j] = ready_queue[j + 1];
            }
            ready_queue[ready_queue_top] = 0;
            ready_queue_top--;
        }
        return 0;
    }
    friend void update_status_file(int pid, const char status[], int t);
};

class Scheduler
{
public:
    void schedule_process(Process_Creator &PC, int simulation_time, int time_quantum, int choice)
    {
        if (choice == 1)
        {
            cout << "I am in schedule process" << endl;
            for (int i = 1; i <= simulation_time; i++)
            {
                implement_algo algo(PC);
                algo.FCFS(PC, i);
            }
            cout << "\nFCFS Scheduling Completed.\n"
                 << endl;
            cout << "Check process.txt and status.txt for output" << endl;

            for (int i = 0; i < num; i++)
            {
                process_details pd;
                PC.processes[i] = new Process(pd);
                update_process_file(pd);
            }
        }

        // else if (choice == 2)
        // {
        //     cout << "\nRound Robin Scheduling Completed.\n"
        //          << endl;
        //     cout << "Checready_queue_top process.txt and status.txt for output" << endl;
        // }
        // else
        // {
        //     cout << "\nCFS Scheduling Completed.\n"
        //          << endl;
        //     cout << "Checready_queue_top process.txt and status.txt for output" << endl;
        // }
    }
    friend class implement_algo;
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

int main()
{
    starter();

    int simulation_time;

    int time_quantum;
    cout << "Enter stimulation time (in milli-seconds) : ";
    cin >> simulation_time;

    // Converting stimulation time into mili-Seconds

    // simulation_time = simulation_time * 1000;

    menu();
    int choice;
    cin >> choice;

    if (!(choice == 1 || choice == 2 || choice == 3))
    {
        cout << "Invalid Input!" << endl;
        exit(1);
    }

    // For RR

    if (choice == 2)
    {
        cout << "Enter time Quantum (in ms) : ";
        cin >> time_quantum;
    }

    // Writing Headers in status.txt and process.txt

    init_status();
    init_process();

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

void init_status()
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

void init_process()
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

void update_status_file(int pid, const char status[], int t)
{
    FILE *fp;
    fp = fopen("status.txt", "a");
    if (fp == NULL)
    {
        printf("\nError file Updating... status.txt !\n");
    }
    fprintf(fp, "%12dms\t\t\t%9d\t\t\t%11s\n", t, pid, status);
    fclose(fp);
}

void update_process_file(process_details PD)
{
    FILE *fp;
    fp = fopen("process.txt", "a");
    if (fp == NULL)
    {
        printf("\nError file Updating... process.txt !\n");
    }
    fprintf(fp, "%9d\t\t%8d ms\t\t%7d ms\t\t%11d ms\t\t%16d ms\t\t%12d ms\t\t%13d ms\n", PD.pid, PD.arr_time, PD.init_brust_time, PD.completion_time, PD.turn_around_time, PD.waiting_time, PD.response_time);
    fclose(fp);
}
