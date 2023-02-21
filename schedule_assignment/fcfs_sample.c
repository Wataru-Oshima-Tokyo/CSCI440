#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;         // process id
    int arrival;    // arrival time
    int burst;      // burst time
    int waiting;    // waiting time
    int turnaround; // turnaround time
};

void FCFS(struct Process processes[], int n) {
    int i, j, total_waiting = 0, total_turnaround = 0;
    processes[0].waiting = 0; // waiting time of first process is 0

    for (i = 1; i < n; i++) {
        processes[i].waiting = 0; // initialize waiting time
        // calculate waiting time of current process
        for (j = 0; j < i; j++) {
            processes[i].waiting += processes[j].burst;
        }
    }

    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].burst + processes[i].waiting;
        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst, processes[i].waiting, processes[i].turnaround);
    }

    printf("Average waiting time = %f\n", (float)total_waiting / n);
    printf("Average turnaround time = %f\n", (float)total_turnaround / n);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time of P%d: ", processes[i].id);
        scanf("%d%d", &processes[i].arrival, &processes[i].burst);
    }
    FCFS(processes, n);
    return 0;
}
