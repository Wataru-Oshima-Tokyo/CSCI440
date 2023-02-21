#include <stdio.h>

#define N 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int queue;
};

struct Queue {
    struct Process processes[N];
    int front;
    int rear;
};

struct Queue queues[3];
int time_quantums[3];

void enqueue(struct Queue* queue, struct Process process) {
    queue->processes[queue->rear] = process;
    queue->rear++;
}

struct Process dequeue(struct Queue* queue) {
    struct Process process = queue->processes[queue->front];
    queue->front++;
    return process;
}

void execute(struct Process process) {
    int i;
    for (i = 0; i < time_quantums[process.queue]; i++) {
        if (process.remaining_time > 0) {
            printf("| P%d ", process.id);
            process.remaining_time--;
        }
    }
    if (process.remaining_time > 0) {
        process.queue++;
        enqueue(&queues[process.queue], process);
    }
}

void execute_all_queues() {
    int time = 0;
    printf("Gantt Chart:\n0");
    while (1) {
        int all_finished = 1;
        int i;
        for (i = 0; i < 3; i++) {
            if (queues[i].front != queues[i].rear) {
                all_finished = 0;
                struct Process process = dequeue(&queues[i]);
                execute(process);
                if (time > 0 && time % 10 == 0) {
                    if (process.queue < 2) {
                        process.queue++;
                    }
                    enqueue(&queues[process.queue], process);
                } else if (process.remaining_time > 0) {
                    enqueue(&queues[process.queue], process);
                }
            }
        }
        if (all_finished) {
            break;
        }
        time++;
    }
    printf("\n");
}

void enqueue_process(struct Process process) {
    enqueue(&queues[0], process);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter the arrival time and burst time of each process:\n");
    for (i = 0; i < n; i++) {
        processes[i].id = i+1;
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].queue = 0;
        enqueue_process(processes[i]);
    }

    time_quantums[0] = 4;
    time_quantums[1] = 8;
    time_quantums[2] = 16;

    execute_all_queues();

    return 0;
}
