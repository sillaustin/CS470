#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_remaining = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && !proc[i].is_completed && proc[i].remaining_time < min_remaining && proc[i].remaining_time > 0) {
            min_remaining = proc[i].remaining_time;
            index = i;
        }
    }
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int completed = 0;
    int current_time = 0;

    //initialize remaining times and completion status
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
    }

    while (completed < n) {
        int idx = findNextProcess(proc, current_time);

        if (idx == -1) {
            //no process ready, advance time
            current_time++;
            continue;
        }

        //execute process for 1 time unit
        proc[idx].remaining_time--;
        current_time++;

        //if process finished
        if (proc[idx].remaining_time == 0) {
            proc[idx].is_completed = 1;
            completed++;

            proc[idx].turnaround_time = current_time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
            if (proc[idx].waiting_time < 0) proc[idx].waiting_time = 0; // Safety
        }
    }
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}
