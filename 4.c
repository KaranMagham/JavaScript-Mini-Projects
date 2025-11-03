#include <stdio.h>
typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;
// Function to calculate waiting and turnaround times
void calculateTimes(Process p[], int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].arrival_time)
        {
            current_time = p[i].arrival_time; // CPU waits if process hasn't arrived
        }
        p[i].waiting_time = current_time - p[i].arrival_time;
        current_time += p[i].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}
// Function to display process table
void printTable(Process p[], int n)
{
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);
    }
}
// Function to calculate and display averages
void calculateAverage(Process p[], int n)
{
    float total_wait = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++)
    {
        total_wait += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f", total_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
}
int main()
{
    int n;
    Process p[100];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Process %d:\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
    }
    // Sort processes by arrival time (FCFS requirement)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
            {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    calculateTimes(p, n);
    printTable(p, n);
    calculateAverage(p, n);
    return 0;
}