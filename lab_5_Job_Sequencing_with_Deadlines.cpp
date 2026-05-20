#include <stdio.h>

struct Job {
    char id;
    int deadline;
    int profit;
};

void jobSequencing(struct Job jobs[], int n) {
    int i, j;

    // 1. Sort all jobs according to profit in descending order using Bubble Sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                struct Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }

    // 2. Find the maximum deadline to determine the size of our timeline
    int maxDeadline = 0;
    for (i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }

    // 3. Initialize the timeline tracking array with empty slots (-1)
    int result[20];
    int slot[20] = {0}; // Tracks whether a slot is filled (1) or free (0)
    for (i = 0; i <= maxDeadline; i++) {
        result[i] = -1;
    }

    int totalProfit = 0;

    // 4. Iterate through all sorted jobs and place them in their latest possible free slot
    for (i = 0; i < n; i++) {
        // Try to schedule from the last possible slot before the deadline backwards
        for (j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) { // Free slot found
                result[j] = i;  // Store index of the job
                slot[j] = 1;    // Mark slot as filled
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // 5. Print the scheduled sequence
    printf("\nScheduled Jobs Sequence: ");
    for (i = 1; i <= maxDeadline; i++) {
        if (slot[i] == 1) {
            printf("%c ", jobs[result[i]].id);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    int n, i;
    struct Job jobs[20];

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    printf("Enter job details (ID Deadline Profit):\n");
    for (i = 0; i < n; i++) {
        // Clear input buffer before reading a character ID safely
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    return 0;
}

// Enter number of jobs: 5
// Enter job details (ID Deadline Profit):
// a 2 100
// b 1 19
// c 2 27
// d 1 25
// e 3 15
//
// Scheduled Jobs Sequence: c a e 
// Total Profit: 142