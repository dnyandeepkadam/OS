#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include<climits>

using namespace std;

// Function to calculate TAT and WT for Non-Preemptive SJF
void nonPreemptiveSJF(vector<int> processes, vector<int> burstTime, vector<int> arrivalTime) {
    int n = processes.size();
    vector<int> tat(n), wt(n), completionTime(n);
    vector<bool> visited(n, false);

    int currentTime = 0, completed = 0;

    while (completed < n) {
        int shortest = -1;
        int minBurstTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && arrivalTime[i] <= currentTime && burstTime[i] < minBurstTime) {
                shortest = i;
                minBurstTime = burstTime[i];
            }
        }

        if (shortest != -1) {
            currentTime += burstTime[shortest];
            completionTime[shortest] = currentTime;
            tat[shortest] = completionTime[shortest] - arrivalTime[shortest];
            wt[shortest] = tat[shortest] - burstTime[shortest];
            visited[shortest] = true;
            completed++;
        } else {
            currentTime++;
        }
    }

    cout << "\nNon-Preemptive SJF Scheduling:\n";
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

// Function to calculate TAT and WT for Preemptive SJF
void preemptiveSJF(vector<int> processes, vector<int> burstTime, vector<int> arrivalTime) {
    int n = processes.size();
    vector<int> remainingTime = burstTime;
    vector<int> tat(n), wt(n), completionTime(n);
    int currentTime = 0, completed = 0;
    int shortest = -1;

    while (completed < n) {
        shortest = -1;
        int minRemainingTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minRemainingTime) {
                shortest = i;
                minRemainingTime = remainingTime[i];
            }
        }

        if (shortest != -1) {
            currentTime++;
            remainingTime[shortest]--;

            if (remainingTime[shortest] == 0) {
                completionTime[shortest] = currentTime;
                tat[shortest] = completionTime[shortest] - arrivalTime[shortest];
                wt[shortest] = tat[shortest] - burstTime[shortest];
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    cout << "\nPreemptive SJF Scheduling:\n";
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

// Menu-driven program
int main() {
    int n;
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

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Non-Preemptive SJF Scheduling\n";
        cout << "2. Preemptive SJF Scheduling\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                nonPreemptiveSJF(processes, burstTime, arrivalTime);
                break;
            case 2:
                preemptiveSJF(processes, burstTime, arrivalTime);
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
//4 //AT 0 1 2 3 //BT 8 4 9 5