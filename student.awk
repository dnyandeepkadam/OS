BEGIN {
    print "Student ID | Name          | Total Marks | Percentage | Result"
    print "------------------------------------------------------------"
}

{
    # Assume the student record contains ID, Name, Marks for 3 subjects
    student_id = $1
    name = $2
    marks1 = $3
    marks2 = $4
    marks3 = $5

    # Calculate total marks and percentage
    total_marks = marks1 + marks2 + marks3
    percentage = (total_marks / 300) * 100

    # Assign result based on percentage
    if (percentage < 40) {
        result = "Fails"
    } else if (percentage >= 60 && percentage <= 65) {
        result = "First Class"
    } else if (percentage > 65) {
        result = "Distinction"
    } else {
        result = "Pass"
    }

    # Print the student details along with the result
    printf "%-12s | %-12s | %-11s | %-10s | %-10s\n", student_id, name, total_marks, percentage, result
}

//awk -f student.awk student.txt