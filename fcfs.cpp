#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
// Function to calculate Turnaround Time (TAT) and Waiting Time (WT)
void calculateTimes(const vector<int>& processes, const vector<int>& burstTime, const vector<int>& arrivalTime, vector<int>& tat, vector<int>& wt) {
    int n = processes.size();
    vector<int> completionTime(n);
    // Calculate Completion Time
    completionTime[0] = arrivalTime[0] + burstTime[0];
    for (int i = 1; i < n; i++) {
        completionTime[i] = max(completionTime[i - 1], arrivalTime[i]) + burstTime[i];
    }
    // Calculate Turnaround Time and Waiting Time
    for (int i = 0; i < n; i++) {
        tat[i] = completionTime[i] - arrivalTime[i];
        wt[i] = tat[i] - burstTime[i];
    }
}

int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processes(n), burstTime(n), arrivalTime(n), tat(n), wt(n);

    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> arrivalTime[i];
        cout << "Burst Time: ";
        cin >> burstTime[i];
        processes[i] = i + 1;
    }

    // Calculate TAT and WT
    calculateTimes(processes, burstTime, arrivalTime, tat, wt);

    // Display results
    cout << "\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i]
             << "\t\t" << tat[i] << "\t\t" << wt[i] << '\n';
    }

    // Calculate and display average TAT and WT
    double avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += tat[i];
        avgWT += wt[i];
    }
    avgTAT /= n;
    avgWT /= n;

    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avgTAT << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWT << endl;

    return 0;
}

//3 //AT 0 1 2 //BT 2 2 20