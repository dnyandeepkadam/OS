#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

// Function to calculate Turnaround Time and Waiting Time using Round Robin Scheduling
void roundRobin(vector<int> processes, vector<int> burstTime, vector<int> arrivalTime, int timeQuantum) {
    int n = processes.size();
    vector<int> remainingTime = burstTime;
    vector<int> completionTime(n), tat(n), wt(n);
    queue<int> readyQueue;

    int currentTime = 0;
    int completed = 0;
    vector<bool> visited(n, false);

    // Add processes to ready queue as per their arrival time
    for (int i = 0; i < n; i++) {
        if (arrivalTime[i] <= currentTime && !visited[i]) {
            readyQueue.push(i);
            visited[i] = true;
        }
    }

    while (!readyQueue.empty() || completed < n) {
        if (!readyQueue.empty()) {
            int currentProcess = readyQueue.front();
            readyQueue.pop();

            if (remainingTime[currentProcess] > 0) {
                int timeToRun = min(remainingTime[currentProcess], timeQuantum);
                currentTime += timeToRun;
                remainingTime[currentProcess] -= timeToRun;

                // If the process is completed
                if (remainingTime[currentProcess] == 0) {
                    completionTime[currentProcess] = currentTime;
                    tat[currentProcess] = completionTime[currentProcess] - arrivalTime[currentProcess];
                    wt[currentProcess] = tat[currentProcess] - burstTime[currentProcess];
                    completed++;
                }
            }

            // Add newly arrived processes to the queue
            for (int i = 0; i < n; i++) {
                if (arrivalTime[i] <= currentTime && !visited[i]) {
                    readyQueue.push(i);
                    visited[i] = true;
                }
            }

            // If the process is not completed, add it back to the ready queue
            if (remainingTime[currentProcess] > 0) {
                readyQueue.push(currentProcess);
            }
        } else {
            currentTime++; // No process is ready, move time forward
            for (int i = 0; i < n; i++) {
                if (arrivalTime[i] <= currentTime && !visited[i]) {
                    readyQueue.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    // Output results
    cout << "\nRound Robin Scheduling:\n";
    cout << "Process\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n";
    double avgTAT = 0, avgWT = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i]
             << "\t\t" << tat[i] << "\t\t" << wt[i] << '\n';
        avgTAT += tat[i];
        avgWT += wt[i];
    }

    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avgTAT / n << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWT / n << endl;
}

// Main function
int main() {
    int n, timeQuantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processes(n), burstTime(n), arrivalTime(n);

    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> arrivalTime[i];
        cout << "Burst Time: ";
        cin >> burstTime[i];
        processes[i] = i + 1;
    }

    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    roundRobin(processes, burstTime, arrivalTime, timeQuantum);

    return 0;
}
//6 //AT 0 1 2 3 4 5 6//BT 4 5 2 1 6 3