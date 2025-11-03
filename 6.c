#include <stdio.h>
typedef struct
{
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
} Process;
int main()
{
    int n, time_quantum, time = 0, completed = 0;
    Process p[100];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    // Input arrival and burst times for all processes
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Process %d Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("Process %d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);
    int done;
    // Loop until all processes are completed
    while (completed != n)
    {
        done = 1;
        for (int i = 0; i < n; i++)
        {
            // Process must have arrived and have remaining time
            if (p[i].arrival_time <= time && p[i].remaining_time > 0)
            {
                done = 0;
                if (p[i].remaining_time > time_quantum)
                {
                    time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                }
                else
                {
                    time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    completed++;
                    p[i].turnaround_time = time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time -
                                        p[i].burst_time;
                }
            }
            else if (p[i].arrival_time > time)
            {
                // If no process has arrived yet, increment time to next arrival
                if (done == 1)
                {
                    time = p[i].arrival_time;
                    done = 0;
                    i--; // Recheck this process after updating time
                }
            }
        }
    }
    // Display results
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    return 0;
}