#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <string>

using namespace std;

class process
{
private:
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
public:
    process()
    {
        pid=0;
        arrival_time=0;
        burst_time=0;
        completion_time=0;
        turn_around_time=0;
        waiting_time=0;
        response_time=0;
    }
    void set_pid(int p)
    {
        pid=p;
    }
    void set_arrival_time(int a)
    {
        arrival_time=a;
    }
    void set_burst_time(int b)
    {
        burst_time=b;
    }
    void set_completion_time(int c)
    {
        completion_time=c;
    }
    void set_turn_around_time(int t)
    {
        turn_around_time=t;
    }
    void set_waiting_time(int w)
    {
        waiting_time=w;
    }
    void set_response_time(int r)
    {
        response_time=r;
    }
    int get_pid()
    {
        return pid;
    }
    int get_arrival_time()
    {
        return arrival_time;
    }
    int get_burst_time()
    {
        return burst_time;
    }
    int get_completion_time()
    {
        return completion_time;
    }
    int get_turn_around_time()
    {
        return turn_around_time;
    }
    int get_waiting_time()
    {
        return waiting_time;
    }
    int get_response_time()
    {
        return response_time;
    }
    void print_process()
    {
        cout<<pid<<"\t"<<arrival_time<<"\t"<<burst_time<<"\t"<<completion_time<<"\t"<<turn_around_time<<"\t"<<waiting_time<<"\t"<<response_time<<endl;
    }
};
class process_creator
{
private:
    int n;
    process *p;
public:
    process_creator()
    {
        n=0;
        p=NULL;
    }
    void set_n(int n)
    {
        this->n=n;
    }
    int get_n()
    {
        return n;
    }
    void create_process()
    {
        p=new process[n];
        for(int i=0;i<n;i++)
        {
            p[i].set_pid(i+1);
            p[i].set_arrival_time(rand()%10);
            p[i].set_burst_time(rand()%10+1);
        }
    }
    void print_process()
    {
        cout<<"PID\tAT\tBT\tCT\tTAT\tWT\tRT"<<endl;
        for(int i=0;i<n;i++)
        {
            p[i].print_process();
        }
    }
};
int main()
{
    char str1[1024];
    srand(time(0));
    process_creator pc;
    int n;
    //cout<< "Enter the number of processes"<<endl;
    //cin>>n;
    pc.set_n(n);
    pc.create_process();
    //pc.print_process();
    cout<<"Enter the name of process:";
    cin>>str1;
    while(1)
    {
    if(strcmp(str1,"FCFS")==0)
    {
        cout<<"FCFS has been selected"<<endl;
        int n;
        int arrival_time;
        int burst_time;
        cout<<"Enter the number of processes: ";
        cin>>n;
        process p[n];
        for(int i=0;i<n;i++)
    	{
        p[i].set_pid(i+1);
        arrival_time = rand() % 10 + 1;
        p[i].set_arrival_time(arrival_time);
        burst_time = rand() % 10 + 1;
        p[i].set_burst_time(burst_time);
    	}
        int total_waiting_time=0;
        int total_turn_around_time=0;
        int total_response_time=0;
        int total_burst_time=0;
        for(int i=0;i<n;i++)
        {
            total_burst_time+=p[i].get_burst_time();
        }
        int completion_time=0;
        for(int i=0;i<n;i++)
        {
            completion_time+=p[i].get_burst_time();
            p[i].set_completion_time(completion_time);
            p[i].set_turn_around_time(p[i].get_completion_time()-p[i].get_arrival_time());
            p[i].set_waiting_time(p[i].get_turn_around_time()-p[i].get_burst_time());
            p[i].set_response_time(p[i].get_waiting_time());
            total_waiting_time+=p[i].get_waiting_time();
            total_turn_around_time+=p[i].get_turn_around_time();
            total_response_time+=p[i].get_response_time();
        }
        cout<<"Process ID\tArrival Time\tBurst Time\tCompletion Time         Turn Around Time\tWaiting Time\tResponse Time"<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<p[i].get_pid()<<"\t\t"<<p[i].get_arrival_time()<<"\t\t"<<p[i].get_burst_time()<<"\t\t"<<p[i].get_completion_time()<<"\t\t\t"<<p[i].get_turn_around_time()<<"\t\t\t"<<p[i].get_waiting_time()<<"\t\t"<<p[i].get_response_time()<<endl;
        }
        //cout<<"Average Waiting Time: "<<(float)total_waiting_time/n<<endl;
        //cout<<"Average Turn Around Time: "<<(float)total_turn_around_time/n<<endl;
        //cout<<"Average Response Time: "<<(float)total_response_time/n<<endl;
        //cout<<"Throughput: "<<(float)n/total_burst_time<<endl;
        return 1;
    }
    else if(strcmp(str1, "RR") == 0)
    {
        cout<<"RR has been selected"<<endl;
        int n;
    int arrival_time;
    int burst_time;
    cout<<"Enter the number of processes: ";
    cin>>n;
    process p[n];
    int i;
    for(i=0;i<n;i++)
    {
        p[i].set_pid(i+1);
        arrival_time = rand() % 10 + 1;
        p[i].set_arrival_time(arrival_time);
        burst_time = rand() % 10 + 1;
        p[i].set_burst_time(burst_time);
    }
    int time=0;
    int quantum;
    cout<<"Enter the quantum: ";
    cin>>quantum;
    int j;
    int k;
    int flag=0;
    int count=0;
    int temp[n];
    for(i=0;i<n;i++)
    {
        temp[i]=p[i].get_burst_time();
    }
    while(1)
    {
        for(i=0,count=0;i<n;i++)
        {
            if(temp[i]==0)
            {
                count++;
                continue;
            }
            if(temp[i]>quantum)
            {
                time+=quantum;
                temp[i]-=quantum;
            }
            else
            {
                time+=temp[i];
                p[i].set_completion_time(time);
                temp[i]=0;
            }
        }
        if(count==n)
        {
            break;
        }
    }
    for(i=0;i<n;i++)
    {
        p[i].set_turn_around_time(p[i].get_completion_time()-p[i].get_arrival_time());
        p[i].set_waiting_time(p[i].get_turn_around_time()-p[i].get_burst_time());
        p[i].set_response_time(p[i].get_waiting_time());
    }
    cout<<"Process ID\tArrival Time\tBurst Time\tCompletion Time         Turn Around Time\tWaiting Time\tResponse Time"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<p[i].get_pid()<<"\t\t"<<p[i].get_arrival_time()<<"\t\t"<<p[i].get_burst_time()<<"\t\t"<<p[i].get_completion_time()<<"\t\t\t"<<p[i].get_turn_around_time()<<"\t\t\t"<<p[i].get_waiting_time()<<"\t\t"<<p[i].get_response_time()<<endl;
    }
    return 1;

    }
    else
    {
        cout<<"Invalid"<<endl;
    }
    }
}
