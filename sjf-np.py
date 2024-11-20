import matplotlib.pyplot as plt

def SJFNonPreemptive(n, pid, at, bt):
    ct = [0] * n
    tt = [0] * n
    wt = [0] * n
    tottt = 0
    totwt = 0
    gantt_chart = []  # To store process execution (pid, start_time, duration)

    # Sort processes by arrival time first and then by burst time
    processes = sorted(zip(pid, at, bt), key=lambda x: (x[1], x[2]))
    pid, at, bt = zip(*processes)

    # Scheduling logic
    current_time = 0
    completed = 0
    is_completed = [False] * n

    while completed != n:
        index = -1
        shortest_bt = float('inf')

        for i in range(n):
            if at[i] <= current_time and not is_completed[i] and bt[i] < shortest_bt:
                shortest_bt = bt[i]
                index = i

        if index == -1:
            current_time += 1  # Increment time if no process is available
        else:
            # Calculate start time and completion time
            start_time = max(current_time, at[index])
            current_time = start_time + bt[index]
            ct[index] = current_time
            tt[index] = ct[index] - at[index]
            wt[index] = tt[index] - bt[index]
            tottt += tt[index]
            totwt += wt[index]

            # Mark process as completed
            is_completed[index] = True
            completed += 1

            # Add to Gantt chart
            gantt_chart.append((pid[index], start_time, bt[index]))

    # Output Process Information
    print("\nProcess ID | AT | BT | CT | TT | WT")
    for i in range(n):
        print(f" {pid[i]}         {at[i]}  {bt[i]}  {ct[i]}   {tt[i]}   {wt[i]}")

    # Averages
    print(f"\nAverage Turnaround Time: {tottt / n:.2f}")
    print(f"Average Waiting Time: {totwt / n:.2f}")

    # Textual Gantt Chart
    print("\nGantt Chart")
    print("|", end="")
    for process, start, duration in gantt_chart:
        print(f" P{process} {' ' * duration}|", end="")
    print("\n")

    # Visual Gantt Chart
    plt.figure(figsize=(10, 3))
    for process, start, duration in gantt_chart:
        plt.barh(y=0, width=duration, left=start, edgecolor='black', label=f"P{process}" if gantt_chart[0][0] == process else "")
        plt.text(start + duration / 2, 0, f"P{process}", ha='center', va='center', color='white', fontsize=10)

    plt.yticks([])
    plt.xlabel("Time")
    plt.title("Gantt Chart - SJF Non-Preemptive Scheduling")
    plt.legend(loc='upper right')
    plt.grid(axis='x', linestyle='--', alpha=0.7)
    plt.show()

# Example usage
n = 3
pid = [1, 2, 3]
at = [0, 1, 2]
bt = [10, 5, 8]

SJFNonPreemptive(n, pid, at, bt)
