#include <stdio.h>
typedef struct
{
    int pid; // Process ID
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
} Process;
int main()
{
    int n, time = 0, completed = 0;
    float total_turnaround = 0, total_waiting = 0;
    Process p[100];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    // Input arrival and burst times
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Process %d Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("Process %d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
        p[i].is_completed = 0;
    }
    while (completed != n)
    {
        int idx = -1;
        int min_bt = 1e9;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= time && !p[i].is_completed)
            {
                if (p[i].burst_time < min_bt)
                {
                    min_bt = p[i].burst_time;
                    idx = i;
                }
                if (p[i].burst_time == min_bt)
                {
                    // Tie-breaker: earlier arrival
                    if (p[i].arrival_time < p[idx].arrival_time)
                    {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1)
        {
            // Process the selected job
            p[idx].completion_time = time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time -
                                     p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            total_turnaround += p[idx].turnaround_time;
            total_waiting += p[idx].waiting_time;
            time = p[idx].completion_time;
            p[idx].is_completed = 1;
            completed++;
        }
        else
        {
            // No process is ready, increment time
            time++;
        }
    }
    // Output the table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    return 0;
}