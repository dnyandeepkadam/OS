import heapq

def calculate_sjf(processes, burst_time, arrival_time, preemptive=True):
    n = len(processes)
    completion_time = [0] * n
    turnaround_time = [0] * n
    waiting_time = [0] * n
    remaining_time = burst_time[:]
    time = 0
    completed = 0
    min_heap = []

    if preemptive:
        # Preemptive SJF
        while completed < n:
            # Add all arrived processes to the heap
            for i in range(n):
                if arrival_time[i] <= time and remaining_time[i] > 0:
                    heapq.heappush(min_heap, (remaining_time[i], i))

            if min_heap:
                # Get the process with the shortest remaining burst time
                shortest, i = heapq.heappop(min_heap)
                time += 1
                remaining_time[i] -= 1
                if remaining_time[i] == 0:
                    completed += 1
                    completion_time[i] = time
            else:
                time += 1
    else:
        # Non-Preemptive SJF
        ready_queue = []
        while completed < n:
            # Add all arrived processes to the ready queue
            for i in range(n):
                if arrival_time[i] <= time and remaining_time[i] > 0:
                    heapq.heappush(ready_queue, (burst_time[i], i))

            if ready_queue:
                # Get the process with the shortest burst time
                burst, i = heapq.heappop(ready_queue)
                time += burst
                completion_time[i] = time
                remaining_time[i] = 0
                completed += 1
            else:
                time += 1

    # Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for i in range(n):
        turnaround_time[i] = completion_time[i] - arrival_time[i]
        waiting_time[i] = turnaround_time[i] - burst_time[i]

    # Display the results
    mode = "Preemptive" if preemptive else "Non-Preemptive"
    print(f"{mode} SJF Scheduling Results:")
    print(f"{'Process':<10}{'Arrival Time':<15}{'Burst Time':<15}{'Completion Time':<20}{'TAT':<10}{'WT':<10}")
    for i in range(n):
        print(f"{processes[i]:<10}{arrival_time[i]:<15}{burst_time[i]:<15}{completion_time[i]:<20}{turnaround_time[i]:<10}{waiting_time[i]:<10}")
    
    # Calculate and display averages
    avg_tat = sum(turnaround_time) / n
    avg_wt = sum(waiting_time) / n
    print(f"\nAverage Turnaround Time: {avg_tat:.2f}")
    print(f"Average Waiting Time: {avg_wt:.2f}")


# Example Input
processes = ["P1", "P2", "P3", "P4"]
burst_time = [6, 8, 7, 3]
arrival_time = [0, 1, 2, 3]

# Run SJF Scheduling
print("===" * 10)
calculate_sjf(processes, burst_time, arrival_time, preemptive=True)
print("===" * 10)
calculate_sjf(processes, burst_time, arrival_time, preemptive=False)