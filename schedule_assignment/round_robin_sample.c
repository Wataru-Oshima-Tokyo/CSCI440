#include <stdio.h>

int main() {
    int n, quantum, i, j, time = 0;
    int burst_time[20], remaining_time[20];
    float waiting_time = 0, turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the burst time for each process: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Execute the processes in a round-robin fashion with incremental time quantum
    printf("\nGantt Chart:\n");
    printf("0 ");
    while (1) {
        int all_finished = 1;
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                all_finished = 0;
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                    printf("| P%d | %d ", i+1, time);
                } else {
                    time += remaining_time[i];
                    waiting_time += time - burst_time[i];
                    turnaround_time += time;
                    remaining_time[i] = 0;
                    printf("| P%d | %d ", i+1, time);
                }
            }
        }
        if (all_finished) {
            break;
        }
    }

    // Calculate and print the average waiting time and average turnaround time
    printf("\n\nAverage Waiting Time: %f", waiting_time/n);
    printf("\nAverage Turnaround Time: %f\n", turnaround_time/n);
    return 0;
}
