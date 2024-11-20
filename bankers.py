def is_safe(available, max_demand, allocation, need, num_processes, num_resources):
    work = available[:]
    finish = [False] * num_processes
    safe_sequence = []

    while len(safe_sequence) < num_processes:
        allocated_in_this_round = False
        for i in range(num_processes):
            if not finish[i] and all(need[i][j] <= work[j] for j in range(num_resources)):
                for j in range(num_resources):
                    work[j] += allocation[i][j]
                finish[i] = True
                safe_sequence.append(i)
                allocated_in_this_round = True

        if not allocated_in_this_round:
            return False, []

    return True, safe_sequence

def main():
    num_processes = int(input("Enter number of processes: "))
    num_resources = int(input("Enter number of resources: "))

    available = list(map(int, input("Enter available resources (space-separated): ").split()))

    max_demand = []
    print("Enter max demand matrix:")
    for i in range(num_processes):
        max_demand.append(list(map(int, input(f"Process {i}: ").split())))

    allocation = []
    print("Enter allocation matrix:")
    for i in range(num_processes):
        allocation.append(list(map(int, input(f"Process {i}: ").split())))

    need = []
    for i in range(num_processes):
        need.append([max_demand[i][j] - allocation[i][j] for j in range(num_resources)])

    safe, safe_sequence = is_safe(available, max_demand, allocation, need, num_processes, num_resources)

    if safe:
        print("System is in a safe state.")
        print("Safe sequence:", " -> ".join(f"P{p}" for p in safe_sequence))
    else:
        print("System is not in a safe state.")

if __name__ == "__main__":
    main()
# Enter number of processes: 5
# Enter number of resources: 3
# Enter available resources (space-separated): 3 3 2
# Enter max demand matrix:
# Process 0: 7 5 3
# Process 1: 3 2 2
# Process 2: 9 0 2
# Process 3: 4 2 2
# Process 4: 5 3 3
# Enter allocation matrix:
# Process 0: 0 1 0
# Process 1: 2 0 0
# Process 2: 3 0 2
# Process 3: 2 1 1
# Process 4: 0 0 2
# System is in a safe state.
# Safe sequence: P1 -> P3 -> P4 -> P0 -> P2