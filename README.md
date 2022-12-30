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


