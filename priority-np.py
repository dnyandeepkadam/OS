import matplotlib.pyplot as plt

def PriorityNonPreemptive(n, pid, at, bt, priority):
    wt = [0] * n
    tt = [0] * n
    ct = [0] * n
    tottt = 0
    totwt = 0
    completed = [False] * n
    t = 0
    gantt_chart = []  # Store (process_id, start_time, duration)

    # Process scheduling
    for _ in range(n):
        highest_priority = float('inf')
        selected = -1

        for i in range(n):
            if at[i] <= t and not completed[i] and priority[i] < highest_priority:
                highest_priority = priority[i]
                selected = i

        if selected == -1:  # No process is ready, increment time
            t += 1
            continue

        start_time = t
        t += bt[selected]
        ct[selected] = t
        tt[selected] = ct[selected] - at[selected]
        wt[selected] = tt[selected] - bt[selected]
        completed[selected] = True
        tottt += tt[selected]
        totwt += wt[selected]

        # Add to Gantt chart
        gantt_chart.append((pid[selected], start_time, bt[selected]))

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
    plt.title("Gantt Chart - Priority Non-Preemptive Scheduling")
    plt.legend(loc='upper right')
    plt.grid(axis='x', linestyle='--', alpha=0.7)
    plt.show()


# Example usage
n = 4
pid = [1, 2, 3, 4]
at = [0, 1, 2, 3]
bt = [8, 4, 9, 5]
priority = [2, 1, 4, 3]

PriorityNonPreemptive(n, pid, at, bt, priority)
