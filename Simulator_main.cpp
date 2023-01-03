#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>

#define num_of_process 20
#define MAX_SIZE 999999

using namespace std;

// Starter menu Functions

void starter();
void menu();

// File Handling Function

void initilize_header_to_status_file();
void initilize_header_to_process_file();
void write_update_to_status_file(process_details PD, const char status[], int t);

// Class Queue and its Functions

class Queue
{
    Process **arr;
    int front;
    int back;
    int size;

public:
    Queue()
    {
        arr = new Process *[MAX_SIZE];
        front = 0;
        back = -1;
        size = 0;
    };
    void enqueue(Process x)
    {
        if (size == MAX_SIZE)
        {
            cout << "Error: Queue is full" << endl;
            return;
        }
        back = (back + 1) % MAX_SIZE;
        *arr[back] = x;
        size++;
    }
    void dequeue()
    {
        if (size == 0)
        {
            cout << "Error: Queue is empty" << endl;
            return;
        }
        front = (front + 1) % MAX_SIZE;
        size--;
    }
    Process peak()
    {
        if (size == 0)
        {
            cout << "Error: Queue is empty" << endl;
            exit(1);
        }
        return *arr[front];
    }
    Process back_ele()
    {
        if (size == 0)
        {
            cout << "Error: Queue is empty" << endl;
            exit(1);
        }
        return *arr[back];
    }
    int Size() { return size; }
    bool isEmpty()
    {
        if (front == -1 || front > back)
        {
            return true;
        }
        return false;
    }
    friend class Process;
    friend class Scheduler;
    friend class Simulator;
    friend class Schedular_FCFS;
};

// void Queue ::enqueue(Process x)
// {
// }
// void Queue ::dequeue()
// {
//     if (size == 0)
//     {
//         cout << "Error: Queue is empty" << endl;
//         return;
//     }
//     front = (front + 1) % MAX_SIZE;
//     size--;
// }
// Process Queue ::peak()
// {

//     if (size == 0)
//     {
//         cout << "Error: Queue is empty" << endl;
//         exit(1);
//     }
//     return *arr[front];
// }

// Process Queue ::back_ele()
// {
//     if (size == 0)
//     {
//         cout << "Error: Queue is empty" << endl;
//         exit(1);
//     }
//     return *arr[back];
// }
// int Queue::Size()
// {
//     return size;
// }

// bool Queue ::isEmpty()
// {
//     if (front == -1 || front > back)
//     {
//         return true;
//     }
//     return false;
// }

// For storing Various Details of a process

class process_details
{

    int pid;
    int arr_time;
    int brust_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int completion_time;

public:
    friend void write_update_to_status_file(process_details PD, const char status[], int t);
    friend class Process;
    friend class Process_Creator;
    friend class Scheduler;
    friend class Simulator;
    friend class Schedular_FCFS;
};

// Class process - which will assign values to the data members and print them

class Process
{
    process_details processes_data;

public:
    // Constructor For assigning Values

    Process(process_details pd)
    {
        processes_data.pid = pd.pid;
        processes_data.arr_time = pd.arr_time;
        processes_data.brust_time = pd.brust_time;
        processes_data.completion_time = pd.completion_time;
        processes_data.turn_around_time = pd.turn_around_time;
        processes_data.waiting_time = pd.waiting_time;
        processes_data.response_time = pd.response_time;
        // processes_data.burstTime1 = PD.burstTime1;
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
        // this->Data.burstTime1 = PD.burstTime1;
    }
    // void runOneUnit()
    // {
    //     Data.burstTime = Data.burstTime - 1;
    //     return;
    // }
    // function to display Process Properties
    // void printProcessDetails()
    // {
    //     printProcessInformation(Data);
    // }
    // void printPidATBT()
    // {
    //     printProcessIdATBT(Data);
    // }
    int get_pid() const { return processes_data.pid; }
    int get_arr_time() const { return processes_data.arr_time; }
    int get_brust_time() const { return processes_data.brust_time; }
    // friend class Scheduler;
    // friend class Simulator;
    // friend class FCFSScheduler;
    // friend class SRTFScheduler;
    // friend class RRScheduler;
    friend class Process_Creator;
    friend class Scheduler;
    friend class Simulator;
    friend class Schedular_FCFS;
};

class Process_Creator
{

    // Array of Processes
    Process **processes;

public:
    Process_Creator()
    {
        process_details pd;

        pd.completion_time = 0;
        pd.turn_around_time = 0;
        pd.waiting_time = 0;
        pd.response_time = 0;

        // Allocates Memory for the Array

        processes = new Process *[num_of_process];

        // Initializing the arrival time and burst time with Random Values

        for (int i = 0; i < num_of_process; i++)
        {
            pd.pid = i;
            pd.arr_time = rand() % 10;
            pd.brust_time = 1 + rand() % 10;
            // Storing diff Process index wise in each index of processes Array
            processes[i] = new Process(pd);
        }
        for (int i = 0; i < num_of_process; i++)
        {
            processes[i];
        }
    }

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

    // Scheduler as Friend class for Process_Creator
    // Scheduler can access the private members of this class
    friend class Process;
    friend class Scheduler;
    friend class Simulator;
    friend class Schedular_FCFS;
};

class Schedular
{

public:
    void schedule_processes(Process_Creator pc, int simulation_time, int time_quantum, string sAlgorithm)
    {
        // string fa = "FCFS";
        // string sa = "RR";
        // string ta = "CFS";
        if (sAlgorithm == "FCFS")
        {
            Schedular_FCFS Fcfs(pc);
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
            return;
        }
    }
    friend class Simulator;
};

class Schedular_FCFS
{
    Queue ready_queue;

public:
    Schedular_FCFS(Process_Creator &PC)
    {
        // Constructor of the Class
    }
    void checkProcessesArrival(Process_Creator &pc, int t)
    {
        for (int i = 0; i < num_of_process; i++)
        {
            if (pc.processes[i]->processes_data.arr_time == t)
            {
                ready_queue.enqueue(Process(pc.processes[i]->processes_data));
                write_update_to_status_file(pc.processes[i]->processes_data, "Arrived", t);
                cout << "t and AT Matched" << pc.processes[i]->processes_data.arr_time << endl;
            }
        }
    }
    // void writeStatusFile(const char status[], int t)
    // {
    //     Process P = readyQueue.top();
    //     writeDataToStatusFile(P.Data, status, t);
    //     return;
    // }
    // void writeProcessesFile(ProcessDetails_t Data)
    // {
    //     writeDataToProcessesFile(Data);
    // }
    void FCFS(Process_Creator &PC, int t)
    {
        checkProcessesArrival(PC, t);
        if (ready_queue.isEmpty() == false)
        {
            Process P = ready_queue.peak();
            if (P.processes_data.brust_time != 0)
            {
                            // writeStatusFile("Running", t);
                //         P.Data.burstTime -= 1;
                //         if (P.Data.responseTime == -1)
                //         {
                //             P.Data.responseTime = t - P.Data.arrivalTime;
                //         }
                //         readyQueue.pop();
                //         readyQueue.push(Process(P.Data));
                //     }
                
                // P.printProcessDetails();
                // P.printPidATBT();
                // }
            }
            friend class Scheduler;
        };

        class Simulator
        {
        private:
            int simulation_time;
            int time_quantum;
            int num_of_processes;
            string sAlgorithm;

        public:
            Simulator(int sT, int tQ, string sA)
            {
                simulation_time = sT;
                time_quantum = tQ;
                num_of_processes = num_of_process;
                sAlgorithm = sA;
            }

            void init_simulation()
            {
                Process_Creator pc;
                Schedular s;
                s.schedule_processes(pc, simulation_time, time_quantum, sAlgorithm);
            }
            friend class Scheduler;
        };
        int main()
        {
            starter();

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

            Simulator Simulation(simulation_time, time_quantum, salgorithm);
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

        void write_update_to_status_file(process_details PD, const char status[], int t)
        {
            FILE *fp;
            fp = fopen("status.txt", "a");
            if (fp == NULL)
            {
                printf("\nError file Updating... status.txt !\n");
            }
            fprintf(fp, "%010d\t\t%010d\t\t%s\n", t, PD.pid, status);
            fclose(fp);
        }

        void menu()
        {
            cout << "\n**********************************************************\n"
                 << endl;
            cout << "Enter 'FCFS' for First Come First Serve (FCFS) " << endl;
            cout << "Enter 'RR' for Round Robin Scheduling " << endl;
            cout << "Enter 'CFS' for Completely Fair Scheduler (CFS) " << endl;
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
