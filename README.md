# OS+OOPS Assignment - CPU Schdeular

# Nishchhal Pachouri

This assignment is a mix of Operating Systems and Object Oriented Programming concepts. In this
assignment, i will be designing a simulator to simulate the behavior of a CPU scheduler, i.e.,
choosing a process from the ready queue based on a scheduling algorithm to execute it by the
processor. The simulator has to be implemented using C++.

# The simulator will consists of following classes:

# 1.Process

The data members of this class should store process id, arrival time in the ready queue,
CPU burst time, completion time, turn around time, waiting time, and response time. The member
functions of this class should assign values to the data members and print them. A constructor
should also be used.

# 2.Process_Creator

This class will create an array of processes and assign a random arrival time
and burst time to each process. Data members, constructor and member functions can be written
accordingly.

# 3.Scheduler

This class will implement the scheduling algorithm. The class will maintain a ready
queue of infinite capacity (i.e., any number of processes can be accommodated in the queue). The
ready queue should be implemented using the min-Heap data structure where the highest priority
process will be the root. The priority of the process will depend on the scheduling algorithm.
The ready queue (i.e., min-heap) should be implemented as a class where different heap operations
should be its member functions. Students have to implement three scheduling algorithms, viz., First
Come First Serve (FCFS), Round Robin and Completely Fair Scheduler (CFS). While running the
program, the user should be asked the choice of scheduling algorithm. The CFS scheduling will be
implemented using Red Black Tree. So, in case of CFS, ready queue will be implemented using Red
Black Tree.

# To understand the CFS Scheduling following youtube lecture can be followed : https://www.youtube.com/watch?v=scfDOof9pww

# 4.Simulator

This class will start the simulation. If the simulation time is 1 second and arrival
time and burst time of a process are in terms of milliseconds then the class will run a ‘for’ loop from
t=0 to 1000. At each iteration, the class will execute all the necessary functions and capture the
required values.

# The class will also print the output in the following ways:


# (a) A file named as processes.txt will be created which will contain a table as follows.

The file handling coding can be done using C programming.

Here, the number of rows will depend on the number of processes.

# (b) A file named as status.txt which will print a table.

For each millisecond, the file will show the
process id of the processes arrived in the system, running by the processor and exiting from the
system. The number of rows in the table will depend on the number of times the ‘for’ loop is
running, i.e., the number of milliseconds in the simulation time. However, if in a particular
millisecond, no process arrived or exited and the process being run by the processor is the same as
that of previous millisecond then the current millisecond can be skipped from printing in the table.


The main() function should take the following input from the user: (i) Simulation time (ii) Name of 
scheduling algorithm (iii) Time quantum in case of Round Robin.
