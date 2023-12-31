# Scheduling-algorithms-in-a-OS
Evaluating the performance of four scheduling algorithms (FCFS, SJF, RR, and SJRF) implemented in C++ on diverse process sets. These sets, created manually or randomly, aim to assess algorithmic efficiency in terms of average waiting time and turnaround time.

Key-Terms used:<br/>
1.**Process ID**: A special number to identify each task uniquely.<br/>
2.**Arrival Time(AT)**: The moment a task joins the processing queue.<br/>
3.**Burst Time(BT)**: The time a task needs the CPU to finish its job.<br/>
4.**Completion Time(CT)**: When a task is done and no longer needs the CPU.<br/>
5.**Turn Around Time(TAT)**: The total time a task takes from joining the queue until it completes.<br/>
6.**Waiting Time(WT)**: The time a task spends waiting for its turn to use the CPU.<br/>
7.**Time Quantum**: In the Round Robin algorithm, each task gets a fixed amount of time to use the CPU, known as a "quantum."

Algorithms used here:<br/>
1. **First Come First Served (FCFS)**:
Arrange processes in ascending order based on their arrival times. Subsequently, schedule each process after the completion of the previous one, adhering to the specified order. Calculate the average waiting time and turnaround time.

2. **Shortest Job First (SJF)**:
Initiate scheduling at time=0, evaluating whether any processes have arrived. If a process has arrived, add it to the queue; otherwise, increment time by one unit. Select the process with the shortest execution/burst time from the queue using a comparison function (compareByExecution). Add its burst time to the current time. Again, check if  any newly arrived processes could be added to the queue, and repeat the process until the queue is empty.

3. **Round Robin (RR)**:
Employ a fixed time quantum for the Round Robin scheduling algorithm. Allocate each process a predetermined amount of CPU time, preempting it once the time quantum is exhausted, regardless of the remaining execution time.

4. **Shortest Job Remaining First (SJRF)**:
SJRF, a twist on the Shortest Job First (SJF) algorithm, behaves in much the same way. The key difference is that SJRF adds a feature called preemption. What this means is that instead of waiting for the current job to finish, SJRF frequently checks how much time is left for the job currently running. It then compares this with the remaining time of every other job after every short unit of time. This is unlike SJF, where the decision about the shortest job is only made when the current job is completed.

After the completion of all processes, we can compare the algorithm using metrics: Average Waiting time and Average Turnaround time.<br/>
TAT = CT - AT<br/>
WT = TAT - BT
