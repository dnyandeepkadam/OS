import matplotlib.pyplot as plt

def SRTF(n, pid, at, bt):
    remaining_bt = bt.copy()
    wt = [0] * n
    tt = [0] * n
    ct = [0] * n
    tottt = 0
    totwt = 0
    t = 0
    complete = 0
    gantt_chart = []  # To store the Gantt chart as (process_id, start_time, duration)
    prev_process = -1

    while complete != n:
        shortest = -1
        min_remaining_time = float('inf')

        # Find the process with the shortest remaining time
        for i in range(n):
            if at[i] <= t and remaining_bt[i] > 0 and remaining_bt[i] < min_remaining_time:
                min_remaining_time = remaining_bt[i]
                shortest = i

        # If no process is ready to execute, increment time
        if shortest == -1:
            t += 1
            continue

        # Add to Gantt chart if the process changes
        if prev_process != shortest:
            if prev_process != -1:
                gantt_chart[-1] = (gantt_chart[-1][0], gantt_chart[-1][1], t - gantt_chart[-1][1])
            gantt_chart.append((pid[shortest], t, 0))
            prev_process = shortest

        # Process the selected shortest job
        remaining_bt[shortest] -= 1

        # Increment time
        t += 1

        # If the process has completed, calculate its turnaround time and waiting time
        if remaining_bt[shortest] == 0:
            complete += 1
            ct[shortest] = t
            tt[shortest] = ct[shortest] - at[shortest]
            wt[shortest] = tt[shortest] - bt[shortest]
            tottt += tt[shortest]
            totwt += wt[shortest]

    # Finalize last process in the Gantt chart
    if gantt_chart:
        gantt_chart[-1] = (gantt_chart[-1][0], gantt_chart[-1][1], t - gantt_chart[-1][1])

    # Output Process Information
    print("\nProcess ID | AT | BT | CT | TT | WT")
    for i in range(n):
        print(f" {pid[i]}        {at[i]}    {bt[i]}   {ct[i]}   {tt[i]}   {wt[i]}")

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
    plt.figure(figsize=(12, 3))
    for process, start, duration in gantt_chart:
        plt.barh(y=0, width=duration, left=start, edgecolor='black', label=f"P{process}" if gantt_chart[0][0] == process else "")
        plt.text(start + duration / 2, 0, f"P{process}", ha='center', va='center', color='white', fontsize=10)

    plt.yticks([])
    plt.xlabel("Time")
    plt.title("Gantt Chart - SRTF Scheduling")
    plt.grid(axis='x', linestyle='--', alpha=0.7)
    plt.show()


# Example usage
n = 4
pid = [1, 2, 3, 4]
at = [0, 1, 2, 3]
bt = [6, 2, 8, 3]
SRTF(n, pid, at, bt)