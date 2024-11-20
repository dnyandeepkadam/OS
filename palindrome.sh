#!/bin/bash

# Read the string from the user
echo "Enter a string:"
read str

# Get the length of the string
len=${#str}

# Initialize variables
is_palindrome=1

# Check each character from the beginning with its counterpart from the end
for ((i=0; i<len/2; i++))
do
    if [ "${str:$i:1}" != "${str:$((len-i-1)):1}" ]; then
        is_palindrome=0
        break
    fi
done

# Display the result
if [ $is_palindrome -eq 1 ]; then
    echo "The string '$str' is a palindrome."
else
    echo "The string '$str' is not a palindrome."
fi