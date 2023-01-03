#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <fstream>

#define num_of_process 5
#define MAX_SIZE 999999

using namespace std;

// Starter menu Functions

void starter();
void menu();

// // Class Queue and its Functions

// // class Queue
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

public:
    friend void write_update_to_status_file(process_details PD, const char status[], int t);
    friend void write_update_to_process_file(process_details PD);
    
    friend class Process;
    friend class Process_Creator;
    friend class Scheduler;
    friend class Simulator;
    friend class Schedular_FCFS;
    friend class Scheduler_RR;
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

    friend class Process_Creator;
    friend class Scheduler;
    friend class Schedular_FCFS;
    friend class Simulator;
    friend class Scheduler_RR;
};

class Process_Creator
{

    Process **processes;
    // Array of Processes

public:
    Process_Creator()
    {
        process_details pd;

        pd.completion_time = -1;
        pd.turn_around_time = -1;
        pd.waiting_time = -1;
        pd.response_time = -1;

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
    // friend void check_process_arrival_RR(Process_Creator &PC, int t);
    friend class Process;
    friend class Scheduler;
    friend class Simulator;
    friend class Schedular_FCFS;
    friend class Scheduler_RR;
};

// it will compare two processes arrival and

class FCFS_Comparator
{
public:
    int operator()(const Process &p1, const Process &p2)
    {
        if (p1.get_arr_time() == p2.get_arr_time())
        {
            return p1.get_pid() > p2.get_pid();
        }
        return p1.get_arr_time() > p2.get_arr_time();
    }
};

class Schedular_FCFS
{
    priority_queue<Process, vector<Process>, FCFS_Comparator> ready_queue;

public:
    Schedular_FCFS(Process_Creator &PC)
    {
        // Constructor of the Class
    }
    void check_process_arrival_FCFS(Process_Creator &pc, int t)
    {
        for (int i = 0; i < num_of_process; i++)
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
            // P.print_pid_at_bt();
        }
    }
    friend class Schedular;
};

class RR_Comparator
{
public:
    int operator()(const Process &p1, const Process &p2)
    {
        if (p1.get_arr_time() == p2.get_arr_time())
        {
            return p1.get_pid() > p2.get_pid();
        }
        return p1.get_arr_time() > p2.get_arr_time();
    }
};

class Schedular_RR
{
    // Min Heap ready Queue
    priority_queue<Process, vector<Process>, RR_Comparator> ready_queue;
    priority_queue<Process, vector<Process>, RR_Comparator> ready_queue1;
    int index, time_quantum;

public:
    Schedular_RR(Process_Creator &PC, int tq)
    {
        index = 0;
        time_quantum = tq;
        // Constructor of The Class
    }
    // void check_process_arrival_RR(Process_Creator &PC, int t)
    // {
    //     for (int i = 0; i < num_of_process; i++)
    //     {
    //         if (PC.processes[i]->processes_data.arr_time==t)
    //         {
    //             ready_queue.push(Process(PC.processes[i]->processes_data));
    //             write_update_to_status_file(pc.processes[i]->processes_data, "Arrived", t);
    //             cout << "t and AT Matched" << pc.processes[i]->processes_data.arr_time << endl;
    //         }
    //     }
    // }
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
    void RR(Process_Creator PC, int t)
    {
        // check_process_arrival_RR(PC, t);
        // if (readyQueue.empty() == true && readyQueue1.empty() == false)
        // {
        //     while (readyQueue1.empty() == false)
        //     {
        //         Process P = readyQueue1.top();
        //         readyQueue1.pop();
        //         readyQueue.push(Process(P.Data));
        //     }
        // }
        // if (readyQueue.empty() == false)
        // {
        //     if (counter == timeQuantum)
        //     {
        //         counter = 0;
        //         Process P = readyQueue.top();
        //         readyQueue.pop();
        //         readyQueue1.push(Process(P.Data));
        //         if (readyQueue.empty() == true && readyQueue1.empty() == false)
        //         {
        //             while (readyQueue1.empty() == false)
        //             {
        //                 Process P = readyQueue1.top();
        //                 readyQueue1.pop();
        //                 readyQueue.push(Process(P.Data));
        //             }
        //         }
        //     }
        //     counter += 1;
        // Process P = readyQueue.top();
        // if (P.Data.burstTime != 0)
        // {
        //     writeStatusFile("Running", t);
        //     P.Data.burstTime -= 1;
        //     if (P.Data.responseTime == -1)
        //     {
        //         P.Data.responseTime = t - P.Data.arrivalTime;
        //     }
        //     readyQueue.pop();
        //     readyQueue.push(Process(P.Data));
        // }
        // else
        // {
        //     writeStatusFile("Exit", t);
        //     P.Data.completionTime = t;
        //     P.Data.turnAroundTime = P.Data.completionTime - P.Data.arrivalTime;
        //     P.Data.waitingTime = P.Data.turnAroundTime - P.Data.burstTime1;
        //     writeProcessesFile(P.Data);
        //     readyQueue.pop();
        //     if (readyQueue.empty() == false)
        //     {
        //         P = readyQueue.top();
        //         writeStatusFile("Running", t);
        //         P.Data.burstTime -= 1;
        //         if (P.Data.responseTime == -1)
        //         {
        //             P.Data.responseTime = t - P.Data.arrivalTime;
        //         }
        //         readyQueue.pop();
        //         readyQueue.push(Process(P.Data));
        //     }
        //     printWarningMessage("\nProcess Completed...\n");
        // }
        // P.printProcessDetails();
        // P.printPidATBT();
    }
    friend class Schedular;
};

class Schedular_CFS
{
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
            for (int i = 1; i <= simulation_time; i++)
            {
                cout << "\nIteration is " << i << endl;
                Fcfs.FCFS(pc, i);
            }
            while (Fcfs.ready_queue.empty() == false)
            {
                Process P = Fcfs.ready_queue.top();
                // write_update_to_process_file(P.processes_data);
                Fcfs.ready_queue.pop();
            }
            return;
        }
        else
        {
            // Scheduler_RR Rr(PC, timeQuantum);
            // for (int i = 1; i <= simulationTime; i++)
            // {
            //     cout << "\nIteration is " << i << endl;
            //     Rr.RR(PC, i);
            // }
            // while (Rr.readyQueue.empty() == false)
            // {
            //     Process P = Rr.readyQueue.top();
            //     writeDataToProcessesFile(P.Data);
            //     Rr.readyQueue.pop();
            // }
            // return;
        }
    }

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

// File Handling Function

void initilize_header_to_status_file();
void initilize_header_to_process_file();
void write_update_to_status_file(process_details PD, const char status[], int t);

int main()
{
    starter();

    int time_quantum;
    int simulation_time;
    cout << "Enter stimulation time (in secs) : ";
    cin >> simulation_time;
    // Converting stimulation time into mili-Seconds

    simulation_time = simulation_time * 1000;
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
    fprintf(fp, "%017d\t\t\t%010d\t\t\t%s\n", t, PD.pid, status);
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
    fprintf(fp, "%010d\t\t%012d\t\t%010d\t\t%015d\t\t%016d\t\t%012d\t\t%013d\n", PD.pid, PD.arr_time, PD.brust_time, PD.completion_time, PD.turn_around_time, PD.waiting_time, PD.response_time);
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
