#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    char type[10];
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct {
    Process queue[MAX];
    int front, rear;
} Queue;

typedef struct {
    int process_id;
    int start_time;
    int end_time;
} GanttEntry;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Process p) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->queue[++q->rear] = p;
}

Process dequeue(Queue *q) {
    Process p = q->queue[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return p;
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    Process p[MAX];

    for (int i = 0; i < n; i++) {
        printf("Enter process_id, arrival_time, burst_time, type (system/user): ");
        scanf("%d %d %d %s",
              &p[i].process_id,
              &p[i].arrival_time,
              &p[i].burst_time,
              p[i].type);

        p[i].remaining_time = p[i].burst_time;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    Queue systemQueue, userQueue;
    initQueue(&systemQueue);
    initQueue(&userQueue);

    int time = 0, completed = 0, i = 0;
    Process *current = NULL;

    GanttEntry gantt[MAX];
    int g = 0;

    while (completed < n) {
        while (i < n && p[i].arrival_time <= time) {
            if (strcmp(p[i].type, "system") == 0)
                enqueue(&systemQueue, p[i]);
            else
                enqueue(&userQueue, p[i]);
            i++;
        }

        if (current != NULL) {
            if (strcmp(current->type, "user") == 0 && !isEmpty(&systemQueue)) {
                enqueue(&userQueue, *current);
                free(current);
                current = NULL;
            }
        }
        if (current == NULL) {
            if (!isEmpty(&systemQueue)) {
                Process temp = dequeue(&systemQueue);
                current = (Process *)malloc(sizeof(Process));
                *current = temp;
            } else if (!isEmpty(&userQueue)) {
                Process temp = dequeue(&userQueue);
                current = (Process *)malloc(sizeof(Process));
                *current = temp;
            } else {
                time++;
                continue;
            }

            gantt[g].process_id = current->process_id;
            gantt[g].start_time = time;
        }

        current->remaining_time--;
        time++;

        if (current->remaining_time == 0) {

            int idx = -1;
            for (int k = 0; k < n; k++) {
                if (p[k].process_id == current->process_id) {
                    idx = k;
                    break;
                }
            }

            p[idx].completion_time = time;
            p[idx].turnaround_time = time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            gantt[g].end_time = time;
            g++;

            completed++;
            free(current);
            current = NULL;
        }
    }

    printf("\nGantt Chart:\n");
    for (int k = 0; k < g; k++) {
        printf("| P%d (%d-%d) ",
               gantt[k].process_id,
               gantt[k].start_time,
               gantt[k].end_time);
    }
    printf("|\n");

    printf("\nProcess Table:\n");
    printf("ID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    double totalWT = 0, totalTAT = 0;

    for (int k = 0; k < n; k++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[k].process_id,
               p[k].type,
               p[k].arrival_time,
               p[k].burst_time,
               p[k].completion_time,
               p[k].waiting_time,
               p[k].turnaround_time);

        totalWT += p[k].waiting_time;
        totalTAT += p[k].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
