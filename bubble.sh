#!/bin/bash

# Function to perform Bubble Sort
bubble_sort() {
    local array=("$@")  # Accept array as arguments
    local n=${#array[@]}

    for ((i = 0; i < n - 1; i++)); do
        for ((j = 0; j < n - i - 1; j++)); do
            if ((array[j] > array[j + 1])); then
                # Swap elements
                temp=${array[j]}
                array[j]=${array[j + 1]}
                array[j + 1]=$temp
            fi
        done
    done

    echo "${array[@]}"  # Return sorted array
}

# Read numbers from user
echo "Enter numbers separated by space:"
read -a numbers

# Sort the numbers and display the result
sorted_numbers=$(bubble_sort "${numbers[@]}")
echo "Sorted numbers: $sorted_numbers"