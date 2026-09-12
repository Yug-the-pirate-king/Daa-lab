#include <cstdio>
#include <vector>

struct Job {
    char id;
    int deadline;
    int profit;
};

static void sortJobsByProfitDescending(std::vector<Job>& jobs) {
    for (size_t i = 0; i + 1 < jobs.size(); ++i) {
        for (size_t j = 0; j + 1 < jobs.size() - i; ++j) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

void runJobSequencing(const Job* jobs, int numJobs) {
    if (numJobs <= 0) {
        printf("\nScheduled Jobs Sequence: \nTotal Profit: 0\n");
        return;
    }

    std::vector<Job> sortedJobs(jobs, jobs + numJobs);
    sortJobsByProfitDescending(sortedJobs);

    int timelineSize = numJobs;
    std::vector<int> scheduledJobIndex(timelineSize + 1, -1);
    std::vector<int> slotFilled(timelineSize + 1, 0);
    int totalProfit = 0;

    for (int i = 0; i < numJobs; ++i) {
        int latestSlot = sortedJobs[i].deadline;
        if (latestSlot > timelineSize) {
            latestSlot = timelineSize;
        }

        for (int j = latestSlot; j > 0; --j) {
            if (slotFilled[j] == 0) {
                scheduledJobIndex[j] = i;
                slotFilled[j] = 1;
                totalProfit += sortedJobs[i].profit;
                break;
            }
        }
    }

    printf("\nScheduled Jobs Sequence: ");
    for (int i = 1; i <= timelineSize; ++i) {
        if (slotFilled[i] == 1) {
            printf("%c ", sortedJobs[scheduledJobIndex[i]].id);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    const int MAX_JOBS = 100;
    int numJobs;

    printf("Enter number of jobs: ");
    if (scanf("%d", &numJobs) != 1 || numJobs < 0 || numJobs > MAX_JOBS) {
        printf("Error: number of jobs must be between 0 and %d.\n", MAX_JOBS);
        return 1;
    }

    std::vector<Job> jobs;
    jobs.reserve(numJobs);

    printf("Enter job details (ID Deadline Profit):\n");
    for (int i = 0; i < numJobs; ++i) {
        Job currentJob;

        if (scanf(" %c %d %d", &currentJob.id, &currentJob.deadline, &currentJob.profit) != 3) {
            printf("Error: invalid job details for job %d.\n", i + 1);
            return 1;
        }

        if (currentJob.deadline < 0) {
            printf("Error: deadline for job %d must be non-negative.\n", i + 1);
            return 1;
        }

        jobs.push_back(currentJob);
    }

    runJobSequencing(jobs.data(), static_cast<int>(jobs.size()));
    return 0;
}