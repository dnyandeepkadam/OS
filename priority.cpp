#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <climits>
using namespace std;

// Function to calculate TAT and WT for Non-Preemptive Priority Scheduling
void nonPreemptivePriority(vector<int> processes, vector<int> burstTime, vector<int> arrivalTime, vector<int> priority) {
    int n = processes.size();
    vector<int> tat(n), wt(n), completionTime(n);
    vector<bool> visited(n, false);
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int highestPriority = -1;
        int maxPriority = INT_MIN; // Start with the lowest possible value
        for (int i = 0; i < n; i++) {
            if (!visited[i] && arrivalTime[i] <= currentTime && priority[i] > maxPriority) {
                highestPriority = i;
                maxPriority = priority[i];
            }
        }

        if (highestPriority != -1) {
            currentTime += burstTime[highestPriority];
            completionTime[highestPriority] = currentTime;
            tat[highestPriority] = completionTime[highestPriority] - arrivalTime[highestPriority];
            wt[highestPriority] = tat[highestPriority] - burstTime[highestPriority];
            visited[highestPriority] = true;
            completed++;
        } else {
            currentTime++;
        }
    }

    cout << "\nNon-Preemptive Priority Scheduling:\n";
    cout << "Process\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n";
    double avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << priority[i]
             << "\t\t" << tat[i] << "\t\t" << wt[i] << '\n';
        avgTAT += tat[i];
        avgWT += wt[i];
    }
    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avgTAT / n << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWT / n << endl;
}

// Function to calculate TAT and WT for Preemptive Priority Scheduling
void preemptivePriority(vector<int> processes, vector<int> burstTime, vector<int> arrivalTime, vector<int> priority) {
    int n = processes.size();
    vector<int> remainingTime = burstTime;
    vector<int> tat(n), wt(n), completionTime(n);
    int currentTime = 0, completed = 0;
    int highestPriority = -1;

    while (completed < n) {
        highestPriority = -1;
        int maxPriority = INT_MIN; // Start with the lowest possible value
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && priority[i] > maxPriority) {
                highestPriority = i;
                maxPriority = priority[i];
            }
        }

        if (highestPriority != -1) {
            currentTime++;
            remainingTime[highestPriority]--;
            if (remainingTime[highestPriority] == 0) {
                completionTime[highestPriority] = currentTime;
                tat[highestPriority] = completionTime[highestPriority] - arrivalTime[highestPriority];
                wt[highestPriority] = tat[highestPriority] - burstTime[highestPriority];
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    cout << "\nPreemptive Priority Scheduling:\n";
    cout << "Process\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n";
    double avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << priority[i]
             << "\t\t" << tat[i] << "\t\t" << wt[i] << '\n';
        avgTAT += tat[i];
        avgWT += wt[i];
    }

    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avgTAT / n << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWT / n << endl;
}

// Menu-driven program
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processes(n), burstTime(n), arrivalTime(n), priority(n);
    cout << "Enter Arrival Time, Burst Time, and Priority for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> arrivalTime[i];
        cout << "Burst Time: ";
        cin >> burstTime[i];
        cout << "Priority (higher number = higher priority): ";
        cin >> priority[i];
        processes[i] = i + 1;
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Non-Preemptive Priority Scheduling\n";
        cout << "2. Preemptive Priority Scheduling\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                nonPreemptivePriority(processes, burstTime, arrivalTime, priority);
                break;
            case 2:
                preemptivePriority(processes, burstTime, arrivalTime, priority);
                break;
            case 3:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
//7 //priority 2 4 6 10 8 12 9 //At 0 1 2 3 4 5 6//BT 4 2 3 5 1 4 6 