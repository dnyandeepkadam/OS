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

    # Optimal Page Replacement Algorithm
    for i, page in enumerate(pages):
        if page in frames:
            # Page hit
            page_hits += 1
        else:
            # Page fault
            page_faults += 1

            # Find the optimal page to replace
            if -1 in frames:
                # Fill empty frames first
                empty_index = frames.index(-1)
                frames[empty_index] = page
            else:
                # Determine which page to replace
                future_use = []
                for frame_page in frames:
                    if frame_page in pages[i + 1:]:
                        # Find the next occurrence of the page
                        future_use.append(pages[i + 1:].index(frame_page))
                    else:
                        # If the page is not used in the future, replace it
                        future_use.append(float('inf'))
                
                # Replace the page that is used farthest in the future or not at all
                to_replace_index = future_use.index(max(future_use))
                frames[to_replace_index] = page

        # Display the current state of frames with blocks
        print(f"\nFrame State after accessing page {page}:")
        for j in range(display_frames):
            if frames[j] != -1:
                print(f"| {frames[j]:3d} ", end="")
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

# Enter the total number of pages: 20
# Enter the page reference sequence (space-separated): 
# 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
# Enter the total number of frames: 4
# Enter the number of frames to display in output (up to 4): 4