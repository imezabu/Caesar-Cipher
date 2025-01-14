#!/bin/bash

# Define the arguments
STRING1="Enter Your String"
STRING2="Enter Command"
OUTPUT_FILE="output.txt"

# Clear the output file before appending
> "$OUTPUT_FILE"
#Brute force all shift values
# Loop through integers 0 to 25
for i in {0..25}; do
    # Run the C executable with the arguments
    OUTPUT=$(./your_executable "$STRING1" $i "$STRING2")
    # Append the output string to the file
    echo "$OUTPUT" >> "$OUTPUT_FILE"
done

echo "Execution complete. Results saved in $OUTPUT_FILE."
