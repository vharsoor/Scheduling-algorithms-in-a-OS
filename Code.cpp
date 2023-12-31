#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <map>
using namespace std;

class Task {
    int taskId;
    int executionTime;
    int arrivalTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

public:
    int getId() {
        return taskId;
    }

    int getExecutionTime() {
        return executionTime;
    }

    int getArrivalTime() {
        return arrivalTime;
    }

    int getCompletionTime() {
        return completionTime;
    }

    int getTurnaroundTime() {
        return turnaroundTime;
    }

    int getWaitingTime() {
        return waitingTime;
    }

    void setId(int id) {
        taskId = id;
    }

    void setExecutionTime(int execTime) {
        executionTime = execTime;
    }

    void setArrivalTime(int arrTime) {
        arrivalTime = arrTime;
    }

    void setCompletionTime(int complTime) {
        completionTime = complTime;
    }

    void setTurnaroundTime(int turnTime) {
        turnaroundTime = turnTime;
    }

    void setWaitingTime(int waitTime) {
        waitingTime = waitTime;
    }
};

bool compareByArrival(Task p, Task q) {
    return p.getArrivalTime() < q.getArrivalTime();
}

bool compareByExecution(Task p, Task q) {
    return p.getExecutionTime() < q.getExecutionTime();
}

bool compareById(Task p, Task q) {
    return p.getId() < q.getId();
}
void display(Task tasks[], int taskCount, float avgwt = 0, float avgtat = 0) {
    sort(tasks, tasks + taskCount, compareById);
    cout << "\n\n\t\t The Task Status \n\n";
    cout << "\tTask ID\tArrival Time\tExecution Time\tCompletion Time\tTurnaround Time\tWaiting Time";
    for (int i = 0; i < taskCount; ++i)
        cout << "\n\t\t" << tasks[i].getId() << "\t\t" << tasks[i].getArrivalTime() << "\t\t" << tasks[i].getExecutionTime() << "\t\t"
             << tasks[i].getCompletionTime() << "\t\t" << tasks[i].getTurnaroundTime() << "\t\t" << tasks[i].getWaitingTime();
    cout << "\n\n\t\tAverage Waiting Time: " << avgwt;
    cout << "\n\t\tAverage Turnaround Time: " << avgtat;
    cout << "\n\n\n";
}

void getData(Task tasks[], int &taskCount) {
    int x;
    for (int i = 0; i < taskCount; i++) {
        tasks[i].setId(i + 1);
        cout << "\n\t Task ID: ";
        cout << tasks[i].getId();
        cout << "\n\t Enter the Task Arrival Time: ";
        cin >> x;
        tasks[i].setArrivalTime(x);
        cout << "\n\t Enter the Task Execution Time: ";
        cin >> x;
        tasks[i].setExecutionTime(x);
    }
}

void generateRandomData(Task tasks[], int taskCount) {
    srand(time(NULL));
    for (int i = 0; i < taskCount; i++) {
        tasks[i].setId(i + 1);
        tasks[i].setArrivalTime(rand() % (16));
        tasks[i].setExecutionTime(rand() % 20 + 2);
        tasks[i].setCompletionTime(0);
        tasks[i].setTurnaroundTime(0);
        tasks[i].setWaitingTime(0);
    }
}
void RoundRobin(Task tasks[], int taskCount) {
    cout << "\n\t*** Round Robin ***\n";
    int timeQuantum;
    cout << "\t Time quantum : ";
    cin >> timeQuantum;
    bool inQueue[taskCount + 1];
    fill(inQueue, inQueue + taskCount + 1, false);
    map<int, int> idCompletion;
    int tasksDone = 0, currentTime = 0;
    queue<Task> readyQueue;

    do {
        for (int i = 0; i < taskCount; ++i) {
            if (!inQueue[tasks[i].getId()] && tasks[i].getArrivalTime() == currentTime) {
                readyQueue.push(tasks[i]);
                inQueue[tasks[i].getId()] = true;
            }
        }

        if (!readyQueue.empty()) {
            Task task = readyQueue.front();
            readyQueue.pop();
            int timeSlice = min(timeQuantum, task.getExecutionTime());

            int burst = task.getExecutionTime();
            task.setExecutionTime(burst - timeSlice);

            for (int i = currentTime + 1; i <= currentTime + timeSlice; ++i) {
                for (int j = 0; j < taskCount; ++j) {
                    if (!inQueue[tasks[j].getId()] && tasks[j].getArrivalTime() == i) {
                        readyQueue.push(tasks[j]);
                        inQueue[tasks[j].getId()] = true;
                    }
                }
            }

            currentTime += timeSlice;

            if (task.getExecutionTime() == 0) {
                tasksDone++;
                task.setCompletionTime(currentTime);
                idCompletion[task.getId()] = task.getCompletionTime();
            } else {
                readyQueue.push(task);
            }
        } else {
            currentTime++;
        }
    } while (tasksDone != taskCount);

    float avgWaitTime = 0, avgTurnaroundTime = 0;

    for (int i = 0; i < taskCount; ++i) {
        tasks[i].setCompletionTime(idCompletion[tasks[i].getId()]);
        tasks[i].setTurnaroundTime(tasks[i].getCompletionTime() - tasks[i].getArrivalTime());
        tasks[i].setWaitingTime(tasks[i].getTurnaroundTime() - tasks[i].getExecutionTime());
        avgWaitTime += tasks[i].getWaitingTime();
        avgTurnaroundTime += tasks[i].getTurnaroundTime();
    }

    avgWaitTime = (float)avgWaitTime / taskCount;
    avgTurnaroundTime = (float)avgTurnaroundTime / taskCount;

    display(tasks, taskCount, avgWaitTime, avgTurnaroundTime);
}

void FirstComeFirstServed(Task tasks[], int taskCount) {
    cout << "\n\t*** FCFS ***\n";

    float avgWaitTime = 0, avgTurnaroundTime = 0;

    sort(tasks, tasks + taskCount, compareByArrival);

    for (int i = 0, prevEnd = 0; i < taskCount; i++) {
        tasks[i].setCompletionTime(max(prevEnd, tasks[i].getArrivalTime()) + tasks[i].getExecutionTime());
        tasks[i].setTurnaroundTime(tasks[i].getCompletionTime() - tasks[i].getArrivalTime());
        tasks[i].setWaitingTime(tasks[i].getTurnaroundTime() - tasks[i].getExecutionTime());
        prevEnd = tasks[i].getCompletionTime();

        avgWaitTime += tasks[i].getWaitingTime();
        avgTurnaroundTime += tasks[i].getTurnaroundTime();
    }

    avgWaitTime = (float)avgWaitTime / taskCount;
    avgTurnaroundTime = (float)avgTurnaroundTime / taskCount;

    display(tasks, taskCount, avgWaitTime, avgTurnaroundTime);
}
void ShortestJobFirst(Task tasks[], int taskCount) {
    cout << "\n\t*** SJF ***\n";

    int executedCount = 0;
    bool taskActive[taskCount];
    fill(taskActive, taskActive + taskCount, false);
    vector<Task> tasksInQueue;
    map<int, int> idCompletion;

    for (int time = 0; executedCount < taskCount;) {
        for (int i = 0; i < taskCount; i++) {
            if (!taskActive[tasks[i].getId() - 1] && tasks[i].getArrivalTime() <= time) {
                tasksInQueue.push_back(tasks[i]);
                taskActive[tasks[i].getId() - 1] = true;
            }
        }

        if (!tasksInQueue.empty()) {
            auto minPosition = min_element(tasksInQueue.begin(), tasksInQueue.end(), compareByExecution);
            Task taskMinExecutionTime = *minPosition;
            time += taskMinExecutionTime.getExecutionTime();
            idCompletion[taskMinExecutionTime.getId()] = time;
            executedCount++;
            tasksInQueue.erase(minPosition);
        } else {
            time++;
        }
    }

    float avgWaitTime = 0, avgTurnaroundTime = 0;

    for (int i = 0; i < taskCount; ++i) {
        tasks[i].setCompletionTime(idCompletion[tasks[i].getId()]);
        tasks[i].setTurnaroundTime(tasks[i].getCompletionTime() - tasks[i].getArrivalTime());
        tasks[i].setWaitingTime(tasks[i].getTurnaroundTime() - tasks[i].getExecutionTime());
        avgWaitTime += tasks[i].getWaitingTime();
        avgTurnaroundTime += tasks[i].getTurnaroundTime();
    }

    avgWaitTime = (float)avgWaitTime / taskCount;
    avgTurnaroundTime = (float)avgTurnaroundTime / taskCount;

    display(tasks, taskCount, avgWaitTime, avgTurnaroundTime);
}

void ShortestJobRemainingFirst(Task tasks[], int taskCount) {
    cout << "\n\t*** SJRF ***\n";
    int time = 0, executedCount = 0;
    float avgTurnaroundTime = 0, avgWaitTime = 0;
    vector<Task> tasksInQueue;
    bool inQueue[taskCount];
    fill(inQueue, inQueue + taskCount, false);
    map<int, int> idCompletion;

    while (executedCount != taskCount) {
        for (int i = 0; i < taskCount; i++) {
            if ((tasks[i].getArrivalTime() <= time) && (inQueue[i] == false)) {
                tasksInQueue.push_back(tasks[i]);
                inQueue[i] = true;
            }
        }

        if (!tasksInQueue.empty()) {
            auto minPosition = min_element(tasksInQueue.begin(), tasksInQueue.end(), compareByExecution);
            (*minPosition).setExecutionTime((*minPosition).getExecutionTime() - 1);
            time++;
            if ((*minPosition).getExecutionTime() == 0) {
                idCompletion[(*minPosition).getId()] = time;
                executedCount++;
                tasksInQueue.erase(minPosition);
            }

        } else {
            time++;
        }
    }

    for (int i = 0; i < taskCount; i++) {
        tasks[i].setCompletionTime(idCompletion[tasks[i].getId()]);
        tasks[i].setTurnaroundTime(tasks[i].getCompletionTime() - tasks[i].getArrivalTime());
        tasks[i].setWaitingTime(tasks[i].getTurnaroundTime() - tasks[i].getExecutionTime());
        avgWaitTime += tasks[i].getWaitingTime();
        avgTurnaroundTime += tasks[i].getTurnaroundTime();
    }

    avgWaitTime = (float)avgWaitTime / taskCount;
    avgTurnaroundTime = (float)avgTurnaroundTime / taskCount;

    display(tasks, taskCount, avgWaitTime, avgTurnaroundTime);
}

int main() {
    int Scheduler, InputData, taskCount;
    while (1) {
        cout << "\n\t*****CPU Scheduling Algorithms*****\n";
        cout << "\t 1. First Come First Served (FCFS)\n\t 2. Shortest Job First (SJF)\n\t 3. Round Robin (RR)\n\t 4. Shortest Job Remaining First (SJRF)\n\t 5. All\n\t 0. Exit\n";
        cout << "\n\t Enter your choice [0-5] : ";
        cin >> Scheduler;

        if (Scheduler == 0) {
            exit(1);
        }

        cout << "\n\t Manually enter data or Auto generated data? \n\t 1. Manually \t 2. Random Generated \n";
        cout << "\n\t Enter your choice [1/2] : ";
        cin >> InputData;

        cout << "\t No. of Tasks : ";
        cin >> taskCount;

        Task tasks[taskCount];

        switch (InputData) {
            case 1: {
                getData(tasks, taskCount);
                break;
            }

            case 2: {
                generateRandomData(tasks, taskCount);
            }
        }

        switch (Scheduler) {
            case 1: {
                FirstComeFirstServed(tasks, taskCount);
                break;
            }
            case 2: {
                ShortestJobFirst(tasks, taskCount);
                break;
            }
            case 3: {
                RoundRobin(tasks, taskCount);
                break;
            }
            case 4: {
                ShortestJobRemainingFirst(tasks, taskCount);
                break;
            }
            case 5: {
                FirstComeFirstServed(tasks, taskCount);
                ShortestJobFirst(tasks, taskCount);
                RoundRobin(tasks, taskCount);
                ShortestJobRemainingFirst(tasks, taskCount);
                break;
            }
        }
    }
    return 0;
}
