#!/bin/bash

# Define the path to the binary executable
EXECUTABLE="./main.out"

# Loop through JSON files from 1 to 500
for i in {1..500}; do
  FILE="Instances/cleaned/JSON_${i}.txt"
  if [ -e "$FILE" ]; then
    $EXECUTABLE < "$FILE"
  else
    echo "File not found: $FILE"
  fi
done