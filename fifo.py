def main():
    pages = []
    frames = []
    page_faults = 0
    page_hits = 0

    # Accept the sequence of pages and frame size
    total_pages = int(input("Enter the total number of pages: "))
    print("Enter the page reference sequence (space-separated): ")
    pages = list(map(int, input().split()))

    # Validate the input length
    if len(pages) != total_pages:
        print("Error: The number of pages entered does not match the specified total pages.")
        return

    total_frames = int(input("Enter the total number of frames: "))
    display_frames = int(input(f"Enter the number of frames to display in output (up to {total_frames}): "))
    if display_frames > total_frames:
        display_frames = total_frames

    # Initialize frames to -1 (indicating empty slots)
    frames = [-1] * total_frames
    current_frame = 0

    # FIFO Page Replacement Algorithm
    for page in pages:
        is_page_present = False

        # Check if the current page is already in frames
        if page in frames:
            is_page_present = True
            page_hits += 1

        # If the page is not present, replace the oldest page
        if not is_page_present:
            frames[current_frame] = page  # Replace page
            current_frame = (current_frame + 1) % total_frames  # Update pointer
            page_faults += 1

        # Display the current state of frames with blocks
        print(f"\nFrame State after accessing page {page}:")
        for i in range(display_frames):
            if frames[i] != -1:
                print(f"| {frames[i]:3d} ", end="")
            else:
                print("|     ", end="")
        print("|")

    # Calculate and display page hit ratio and page fault ratio
    hit_ratio = page_hits / total_pages
    fault_ratio = page_faults / total_pages

    print("\n\nTotal Page Hits:", page_hits)
    print("Total Page Faults:", page_faults)
    print(f"Page Hit Ratio: {hit_ratio:.2f}")
    print(f"Page Fault Ratio: {fault_ratio:.2f}")


if __name__ == "__main__":
    main()
# Enter the total number of pages: 15
# Enter the page reference sequence (space-separated): 
# 7 0 1 2 0 3 0 4 2 3 0 3 1 2 0
# Enter the total number of frames: 3
# Enter the number of frames to display in output (up to 3): 3