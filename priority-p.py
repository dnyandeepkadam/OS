import matplotlib.pyplot as plt

def PriorityPreemptive(n, pid, at, bt, priority):
    remaining_bt = bt.copy()
    wt = [0] * n
    tt = [0] * n
    ct = [0] * n
    tottt = 0
    totwt = 0
    t = 0
    complete = 0
    gantt_chart = []  # Store (process_id, start_time, duration)

    # Process scheduling
    while complete != n:
        highest_priority = float('inf')
        shortest = -1

        for i in range(n):
            if at[i] <= t and remaining_bt[i] > 0 and priority[i] < highest_priority:
                highest_priority = priority[i]
                shortest = i

        if shortest == -1:
            t += 1
            continue

        start_time = t
        remaining_bt[shortest] -= 1
        t += 1

        if remaining_bt[shortest] == 0:
            complete += 1
            ct[shortest] = t
            tt[shortest] = ct[shortest] - at[shortest]
            wt[shortest] = tt[shortest] - bt[shortest]
            tottt += tt[shortest]
            totwt += wt[shortest]

        # Update Gantt chart for this time slice
        if gantt_chart and gantt_chart[-1][0] == pid[shortest]:
            gantt_chart[-1] = (pid[shortest], gantt_chart[-1][1], t - gantt_chart[-1][1])  # Extend the duration
        else:
            gantt_chart.append((pid[shortest], start_time, t - start_time))

    # Output Process Information
    print("\nProcess ID | AT | BT | Priority | CT | TT | WT")
    for i in range(n):
        print(f"{pid[i]} \t {at[i]} \t {bt[i]} \t {priority[i]} \t {ct[i]} \t {tt[i]} \t {wt[i]}")

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
    plt.title("Gantt Chart - Priority Preemptive Scheduling")
    plt.legend(loc='upper right')
    plt.grid(axis='x', linestyle='--', alpha=0.7)
    plt.show()


# Example usage
n = 4
pid = [1, 2, 3, 4]
at = [0, 1, 2, 3]
bt = [8, 4, 9, 5]
priority = [2, 1, 4, 3]

PriorityPreemptive(n, pid, at, bt, priority)