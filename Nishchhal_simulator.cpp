#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

#define MAX_SIZE 9999999
#define n 10

void starter();
void menu();

using namespace std;

// Starter menu Functions

void starter();
void menu();

class Process
{
    int pid;
    int arr_time;
    int brust_time;
    int init_brust_time;
    int completion_time;
    int rem_brust_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int executed;
    int vRuntime;
    int priority;

public:
    Process()
    {
        executed = 0;
        pid = 0;
        arr_time = 0;
        turn_around_time = -1;
        brust_time = 0;
        rem_brust_time = 0; // needed to do round robin as in that burst_time will change so remaining burst time needed
        response_time = -1;
        waiting_time = -1;
        completion_time = 0;
    }
    void print_basic_process_info(int pid, int at, int bt)
    {
        cout << "Process ID : " << pid
             << "\tArrival Time : " << at
             << "\tBrust Time : " << bt << endl;
    }
    void Assign(int id, int at, int bt);
    void completion(int);
    void response(int t);
    friend void update_process_file(Process pd);
    friend class Process_Creator;
    friend class Scheduler;
};

void Process::Assign(int id, int at, int bt)
{
    arr_time = at;
    brust_time = bt;
    pid = id;
    rem_brust_time = brust_time;
}

void Process::completion(int completion_time = 0)
{
    this->completion_time = completion_time;
    turn_around_time = completion_time - arr_time;
    waiting_time = turn_around_time - brust_time;
}

void Process::response(int t)
{
    if (response_time == -1)
    {
        response_time = t - arr_time;
    }
}

class Process_Creator
{
private:
    int random_arrival_time;
    int random_brust_time;

public:
    // Allocates Memory for the Array

    Process *arr = new Process[n];

    Process_Creator()
    {
        cout << "\n\t\tProcesses Info\t\t\n"
             << endl;

        for (int i = 0; i < n; i++)
        {
            random_arrival_time = rand() % 20 + 1;
            random_brust_time = rand() % 7 + 1;
            arr[i].Assign(i, random_arrival_time, random_brust_time);
            arr[i].print_basic_process_info(i, random_arrival_time, random_brust_time);
        }
        // cout << "Processes initialised with random Arrival and Brust Time" << endl;
    }
};

// File Handling Functions.

void init_status();
void init_process();
void update_status_file(int pid, const char status[], int t);
void update_process_file(Process PD);

class Scheduler
{
private:
    int ready_queue[n] = {0};
    int queue[n] = {0};
    int ready_queue_top = -1;
    int queue_front_index;
    int init_time = -1;
    int min_burst_time = MAX_SIZE;
    int min_burst_index = -1;

public:
    Process_Creator processes;
    Scheduler()
    {

        queue_front_index = -1;
    }
    bool enqueue(int pid, int t)
    {
        if (queue_front_index == n - 1)
        {
            return false;
        }
        else
        {
            // cout << "enqueued" << endl;
            queue_front_index++;
            queue[queue_front_index] = pid;
            if (queue_front_index == 0)
            {
                init_time = t;
                update_status_file(processes.arr[queue[0]].pid, "arrived", t);
                processes.arr[queue[0]].response(t);
            }
            return true;
        }
    }

    bool dequeue(int t)
    {
        if (queue_front_index == -1)
        {
            return false;
        }
        else
        {
            // cout << "dequeued" << endl;

            int p_executed = queue[0];
            processes.arr[queue[0]].completion(t);
            init_time = t;
            for (int i = 0; i < queue_front_index; i++)
            {

                queue[i] = queue[i + 1];
            }
            queue[queue_front_index] = 0;
            queue_front_index--;
            update_status_file(processes.arr[p_executed].pid, "exit", t);

            if (queue_front_index != -1)
            {

                update_status_file(processes.arr[queue[0]].pid, "arrived", t);
                processes.arr[queue[0]].response(t);
            }
            processes.arr[p_executed].executed = -1;
            return true;
        }
    }

    void FCFS(int t)
    {
        // cout << t << " millisec" << endl;
        for (int i = 0; i < n; i++)
        {
            if (processes.arr[i].executed != -1 && processes.arr[i].arr_time == t)
            {
                ready_queue_top++;
                ready_queue[ready_queue_top] = processes.arr[i].pid;
            }
        }

        if (queue_front_index != -1 && t - init_time == processes.arr[queue[0]].brust_time)
        {
            if (dequeue(t) == 0)
            {
            }
        }
        else if (queue_front_index != -1)
        {
            update_status_file(processes.arr[queue[0]].pid, "running", t);
        }
        if (ready_queue_top != -1 && enqueue(ready_queue[0], t))
        {
            for (int j = 0; j < ready_queue_top; j++)
            {
                ready_queue[j] = ready_queue[j + 1];
            }
            ready_queue[ready_queue_top] = 0;
            ready_queue_top--;
        }
    }

    int context_switch(int t, int time_quantam)
    {
        processes.arr[queue[0]].rem_brust_time = processes.arr[queue[0]].rem_brust_time - time_quantam;
        int id = processes.arr[queue[0]].pid;
        update_status_file(id, "switch", t);

        for (int i = 0; i < queue_front_index; i++)
        {

            queue[i] = queue[i + 1];
        }

        init_time = t;
        queue[queue_front_index] = 0;
        queue_front_index--;
        if (queue_front_index != -1)
        {
            update_status_file(processes.arr[queue[0]].pid, "arrived", t);
        }
        processes.arr[queue[0]].response(t);
        return id;
    }

    int round_robin(int t, int time_quantam)
    {

        // cout << t << " In algo Round_robin is working" << endl;
        int new_process = 0;
        for (int i = 0; i < n; i++)
        {
            if (processes.arr[i].executed != -1 && processes.arr[i].arr_time == t)
            {
                new_process = 1;
                ready_queue_top++;
                ready_queue[ready_queue_top] = processes.arr[i].pid;
            }
        }
        if (new_process == 1)
        {
            for (int i = 0; i <= ready_queue_top; i++)
            {
                if (processes.arr[ready_queue[i]].rem_brust_time < min_burst_time)
                {
                    min_burst_time = processes.arr[ready_queue[i]].brust_time;
                    min_burst_index = i;
                }
            }
        }

        if (queue_front_index != -1 && t - init_time == processes.arr[queue[0]].rem_brust_time)
        {
            if (dequeue(t))
            {
            }
        }
        else if (queue_front_index != -1 && t - init_time == time_quantam)
        {
            ready_queue_top++;
            ready_queue[ready_queue_top] = context_switch(t, time_quantam);
        }
        else
        {
            if (queue_front_index != -1)
            {
                update_status_file(processes.arr[queue[0]].pid, "running", t);
            }
        }

        if (ready_queue_top != -1 && enqueue(ready_queue[min_burst_index], t))
        {
            for (int i = min_burst_index; i < ready_queue_top; i++)
                ready_queue[i] = ready_queue[i + 1];
            ready_queue[ready_queue_top] = 0;
            ready_queue_top--;
            min_burst_index = -1;
            min_burst_time = INT_MAX;
            for (int i = 0; i <= ready_queue_top; i++)
            {
                if (processes.arr[ready_queue[i]].rem_brust_time < min_burst_time)
                {
                    min_burst_time = processes.arr[ready_queue[i]].brust_time;
                    min_burst_index = i;
                }
            }
        }

        return 0;
    }
    void cfs()
    {
    }
};

class Simulator
{
public:
    Scheduler S;
    void simulation(int simulation_time, int choice, int time_quantum = 0)
    {

        for (int t = 1; t <= simulation_time; t++)
        {
            if (choice == 1)
            {
                if (t == 1)
                {
                    cout << "\nFCFS Scheduling Started.\n"
                         << endl;
                }

                S.FCFS(t);
                if (t == simulation_time - 1)
                {
                    cout << "\nFCFS Scheduling Completed.\n"
                         << endl;
                }
            }
            else if (choice == 2)
            {
                if (t == 1)
                {
                    cout << "\nRound robin Scheduling Started.\n"
                         << endl;
                }
                S.round_robin(t, time_quantum);
                if (t == simulation_time - 1)
                {
                    cout << "\nRound Robin Scheduling Completed.\n"
                         << endl;
                }
            }
            else if (choice == 3)
            {
                if (t == 1)
                {
                    cout << "\nCFS Scheduling Started.\n"
                         << endl;
                }
                S.cfs();
                if (t == simulation_time - 1)
                {
                    cout << "\nCFS Scheduling Completed.\n"
                         << endl;
                }
            }
            else
            {
                cout << "Invalid Input ! Try Again" << endl;
                exit(1);
            }
        }

        for (int i = 0; i < n; i++)
        {
            update_process_file(S.processes.arr[i]);
        }
    }
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

    Simulator init;
    init.simulation(simulation_time, choice, time_quantum);
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

void update_process_file(Process PD)
{
    FILE *fp;
    fp = fopen("process.txt", "a");
    if (fp == NULL)
    {
        printf("\nError file Updating... process.txt !\n");
    }
    fprintf(fp, "%9d\t\t%8d ms\t\t%7d ms\t\t%11d ms\t\t%16d ms\t\t%12d ms\t\t%13d ms\n", PD.pid, PD.arr_time, PD.brust_time, PD.completion_time, PD.turn_around_time, PD.waiting_time, PD.response_time);
    fclose(fp);
}
