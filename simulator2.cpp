#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>
#include <iostream>

#define num 7

using namespace std;

void starter();
void menu();

void initilize_header_to_status_file();
void initilize_header_to_process_file();
// void write_update_to_status_file(process_details PD, const char status[], int t);
// void write_update_to_process_file(process_details PD);

class process_details
{
    int pid;
    int arr_time;
    int brust_time;
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
        processes_data.completion_time = pd.completion_time;
        processes_data.turn_around_time = pd.turn_around_time;
        processes_data.waiting_time = pd.waiting_time;
        processes_data.response_time = pd.response_time;
    }
    friend void print_process_details(process_details processes_data);
    friend void print_basic_process_info(process_details processes_data);
    friend class Process_Creator;
};

void print_process_details(process_details processes_data)
{

    cout << "\n";
    cout << "Process ID : " << processes_data.pid << endl;
    cout << "Arrival Time : " << processes_data.arr_time << endl;
    cout << "Brust Time : " << processes_data.brust_time << endl;
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
            // Storing diff Process index wise in each index of processes Array
            processes[i] = new Process(pd);
            print_basic_process_info(processes[i]->processes_data);
        }
    }
    friend void print_process_details(process_details processes_data);
    friend void print_basic_process_info(process_details processes_data);
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
        // Schedular s;
        // s.schedule_processes(pc, simulation_time, time_quantum, sAlgorithm);
    }
    friend class Scheduler;
};

int main()
{
    starter();

    int simulation_time;

    int time_quantum;
    cout << "Enter stimulation time (in secs) : ";
    cin >> simulation_time;
    // Converting stimulation time into mili-Seconds
    simulation_time = simulation_time * 1000;
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

// void write_update_to_status_file(process_details PD, const char status[], int t)
// {
//     FILE *fp;
//     fp = fopen("status.txt", "a");
//     if (fp == NULL)
//     {
//         printf("\nError file Updating... status.txt !\n");
//     }
//     fprintf(fp, "%017d\t\t\t%010d\t\t\t%s\n", t, PD.pid, status);
//     fclose(fp);
// }
// void write_update_to_process_file(process_details PD)
// {
//     FILE *fp;
//     fp = fopen("process.txt", "a");
//     if (fp == NULL)
//     {
//         printf("\nError file Updating... process.txt !\n");
//     }
//     fprintf(fp, "%010d\t\t%012d\t\t%010d\t\t%015d\t\t%016d\t\t%012d\t\t%013d\n", PD.pid, PD.arr_time, PD.brust_time, PD.completion_time, PD.turn_around_time, PD.waiting_time, PD.response_time);
//     fclose(fp);
// }