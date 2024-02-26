#include <stdio.h>
struct process
{
int at; //arrival time to be updated
int at_actual; // actual arrival time
int bt1; //CPU burst time before IO
int bt2; //CPU burst time after IO
int io; //IO burst time
int status;// completed -1, not yet completed - 0
int ft; // finish time
int pid;
}ready_list[10], temp;
int n, cur_time=0, idle_time=0;
int dispatcher();
void sortReadyList();
int main()
{
int i,j,pid, p=100;
printf("Enter number of processes:");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("Process %d\n",i+1);
printf("***********\n");
printf("Enter Arrival Time:");
scanf("%d",&ready_list[i].at);
ready_list[i].at_actual=ready_list[i].at;
printf("Enter burst Time1:");
scanf("%d",&ready_list[i].bt1);
printf("IO burst time:");
scanf("%d",&ready_list[i].io);
printf("Enter burst Time2:");
scanf("%d",&ready_list[i].bt2);
ready_list[i].status=0; // 0 - not yet completed, 1 - already completed
ready_list[i].pid= p++;
}
i=0;
// Until all the n processes are completed
while(i < n)
{
pid=dispatcher(); // To identify the next process to be scheduled
if(ready_list[pid].status == 1)
{
i++;
ready_list[pid].ft=cur_time;
}

}
printf("Process Id\tFinish Time\tTT\n");
printf("**********\t***********\t**\n");
for(i=0;i<n;i++)
{
printf("%d\t\t%d\t\t%d\n",ready_list[i].pid,ready_list[i].ft,(ready_list[i].ft
-ready_list[i].at_actual)) ;
}
// total time that CPU was not running any processes
printf("Total CPU idle time: %d", idle_time);
}
// Function to pick the next process with lowest arrival time
int dispatcher()
{
int i,index=-1,j;
back:
sortReadyList();
for(i=0;i<n;i++)
{
// To check that ith process has arrived either newly or after IO
if(ready_list[i].at <= cur_time)
{
// To check that ith process is not yet completed
if(ready_list[i].status != 1)
{
// To check that first CPU burst is completed or not

if(ready_list[i].bt1 > 0)

{
cur_time = cur_time + ready_list[i].bt1;
// Updated arrival time after IO completion
ready_list[i].at = cur_time + ready_list[i].io;

ready_list[i].bt1 = 0;
index=i; // index of the process that is currently chosen
}

// To check that second CPU burst is completed or not
else if(ready_list[i].bt2 > 0)

{
ready_list[i].status = 1; // Since second BT is completed
cur_time = cur_time + ready_list[i].bt2;
ready_list[i].bt2 = 0;
index=i; // index of the process that is currently chosen
}

break; // Since next process is chosen, end the loop

}

}
}
if(index == -1) // Next process not yet available at the current time
{
cur_time++; // To move the clock until it reach the arrival time of next process
idle_time++; // Since CPU has been idle waiting for next process
goto back;
}
return index;
}
void sortReadyList() // To sort processes as per arrival time
{
int i,j;
for(i=0;i<n-1;i++)
for(j=0;j<n-1;j++)
{
if(ready_list[j].at > ready_list[j+1].at)
{
temp=ready_list[j];
ready_list[j]=ready_list[j+1];
ready_list[j+1]=temp;
}
}
}