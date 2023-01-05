#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

#define MAX_SIZE 9999999
#define n 100

void starter();
void menu();

using namespace std;

// Starter menu Functions

void starter();
void menu();

// Implementing Red-Black Tree in C++

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};

typedef Node *NodePtr;

class RedBlackTree
{
private:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent)
    {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    // Preorder
    void preOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Inorder
    void inOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key)
    {
        if (node == TNULL || key == node->data)
        {
            return node;
        }

        if (key < node->data)
        {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // For balancing the tree after deletion
    void deleteFix(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == 0)
                    {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == 0)
                    {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key)
    {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL)
        {
            if (node->data == key)
            {
                z = node;
            }

            if (node->data <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == TNULL)
        {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0)
        {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == 1)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper(NodePtr root, string indent, bool last)
    {
        if (root != TNULL)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void preorder()
    {
        preOrderHelper(this->root);
    }

    void inorder()
    {
        inOrderHelper(this->root);
    }

    void postorder()
    {
        postOrderHelper(this->root);
    }

    NodePtr searchTree(int k)
    {
        return searchTreeHelper(this->root, k);
    }

    NodePtr minimum(NodePtr node)
    {
        while (node->left != TNULL)
        {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != TNULL)
        {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x)
    {
        if (x->right != TNULL)
        {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x)
    {
        if (x->left != TNULL)
        {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x)
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(int key)
    {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        insertFix(node);
    }

    NodePtr getRoot()
    {
        return this->root;
    }

    void deleteNode(int data)
    {
        deleteNodeHelper(this->root, data);
    }

    void printTree()
    {
        if (root)
        {
            printHelper(this->root, "", true);
        }
    }
};

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
    int virtual_run_time;

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

        cout << "process object created" << endl;
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
    int random_arrival_time; // to store random arrival time
    int random_brust_time;   // to store random burst time

public:
    // Allocates Memory for the Array

    Process *arr = new Process[n];

    Process_Creator()
    {
        cout << "\n\t\tProcesses Info\t\t\n"
             << endl;

        for (int i = 0; i < n; i++)
        {
            random_arrival_time = rand() % 10;
            random_brust_time = rand() % 10 + 1;
            arr[i].Assign(i, random_arrival_time, random_brust_time);
            arr[i].print_basic_process_info(i, random_arrival_time, random_brust_time);
        }
        cout << "Processes initialised with random Arrival and Brust Time" << endl;
    }
};

// File Handling Functions.

void init_status();
void init_process();
void update_status_file(int pid, char status[], int t);
void update_process_file(Process PD);

class Scheduler
{
private:
    int queue[n] = {0};
    int ready_queue[n] = {0};
    int ready_queue_top = -1;
    int queue_front_index;
    int init_time = -1;
    int min_burst_time = MAX_SIZE;
    int min_burst_index = -1;

public:
    Process_Creator processes;
    Scheduler()
    {
        cout << "scheduler running" << endl;
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
            cout << "enqueued" << endl;
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
            cout << "dequeued" << endl;

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
        cout << t << " millisec" << endl;
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
        // cout << t << " millisec" << endl;
        // cout << t << " In algo Round_robin" << endl;
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
                S.FCFS(t);
            }
            else if (choice == 2)
            {
                S.round_robin(t, time_quantum);
            }
            else if (choice == 3)
            {
                S.cfs();
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

void update_status_file(int pid, char status[], int t)
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