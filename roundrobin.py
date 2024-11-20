import matplotlib.pyplot as plt

def RoundRobin(n, pid, at, bt, quantum):
    remaining_bt = bt.copy()  # Copy of burst times to track remaining burst times
    wt = [0] * n  # Waiting times for each process
    tt = [0] * n  # Turnaround times for each process
    ct = [0] * n  # Completion times for each process
    tottt = 0  # Total turnaround time
    totwt = 0  # Total waiting time
    t = 0  # Current time
    gantt_chart = []  # Gantt chart representation (process, start_time, duration)

    while True:
        done = True
        for i in range(n):
            if remaining_bt[i] > 0:
                done = False
                if remaining_bt[i] > quantum:
                    gantt_chart.append((pid[i], t, quantum))  # Record execution
                    t += quantum
                    remaining_bt[i] -= quantum
                else:
                    gantt_chart.append((pid[i], t, remaining_bt[i]))  # Record execution
                    t += remaining_bt[i]
                    remaining_bt[i] = 0
                    ct[i] = t
                    tt[i] = ct[i] - at[i]
                    wt[i] = tt[i] - bt[i]
                    tottt += tt[i]
                    totwt += wt[i]
        
        if done:
            break

    # Output Process Information
    print("\nProcess ID | AT | BT | CT | TT | WT")
    for i in range(n):
        print(f" {pid[i]}      {at[i]}  {bt[i]}  {ct[i]}  {tt[i]}  {wt[i]}")

    # Averages
    print(f"\nAverage Turnaround Time: {tottt / n:.2f}")
    print(f"Average Waiting Time: {totwt / n:.2f}")

    # Visual Gantt Chart
    plt.figure(figsize=(10, 3))
    for process, start, duration in gantt_chart:
        plt.barh(y=0, width=duration, left=start, edgecolor='black', label=f"P{process}" if process == gantt_chart[0][0] else "")
        plt.text(start + duration / 2, 0, f"P{process}", ha='center', va='center', color='white', fontsize=10)

    plt.yticks([])
    plt.xlabel("Time")
    plt.title("Gantt Chart - Round Robin Scheduling")
    plt.legend(loc='upper right')
    plt.grid(axis='x', linestyle='--', alpha=0.7)
    plt.show()


# Example usage
n = 3
pid = [1, 2, 3]
at = [0, 1, 2]
bt = [10, 5, 8]
quantum = 4
RoundRobin(n, pid, at, bt, quantum)