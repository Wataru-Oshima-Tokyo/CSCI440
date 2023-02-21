#include <stdio.h>

#define N 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

struct Queue {
    struct Process processes[N];
    int front;
    int rear;
};

struct Queue queue0, queue1, queue2;
int time_quantum0, time_quantum1, time_quantum2;

void enqueue(struct Queue* queue, struct Process process) {
    queue->processes[queue->rear] = process;
    queue->rear++;
}

struct Process dequeue(struct Queue* queue) {
    struct Process process = queue->processes[queue->front];
    queue->front++;
    return process;
}

void execute(struct Process process, int time_quantum) {
    int i;
    for (i = 0; i < time_quantum; i++) {
        if (process.remaining_time > 0) {
            printf("| P%d ", process.id);
            process.remaining_time--;
        }
    }
}

void execute_queue(struct Queue* queue, int time_quantum) {
    while (queue->front != queue->rear) {
        struct Process process = dequeue(queue);
        execute(process, time_quantum);
        if (process.remaining_time > 0) {
            enqueue(queue, process);
        }
    }
}

void execute_all_queues() {
    printf("Gantt Chart:\n0");
    while (1) {
        if (queue0.front != queue0.rear) {
            execute_queue(&queue0, time_quantum0);
        }
        if (queue1.front != queue1.rear) {
            execute_queue(&queue1, time_quantum1);
        }
        if (queue2.front != queue2.rear) {
            execute_queue(&queue2, time_quantum2);
        }
        if (queue0.front == queue0.rear && queue1.front == queue1.rear && queue2.front == queue2.rear) {
            break;
        }
    }
    printf("\n");
}

void enqueue_process(struct Process process) {
    if (process.priority == 0) {
        enqueue(&queue0, process);
    } else if (process.priority == 1) {
        enqueue(&queue1, process);
    } else {
        enqueue(&queue2, process);
    }
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter the arrival time, burst time and priority of each process:\n");
    for (i = 0; i < n; i++) {
        processes[i].id = i+1;
        scanf("%d%d%d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        enqueue_process(processes[i]);
    }

    printf("Enter the time quantum for each queue: ");
    scanf("%d%d%d", &time_quantum0, &time_quantum1, &time_quantum2);

    execute_all_queues();

    return 0;
}
