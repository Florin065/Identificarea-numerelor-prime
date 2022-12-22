#!/bin/bash

# Script to compare output files in outFermat/ to reference files in ref/
# Generates total accuracy report

# First, set up variables
OUT_DIR="outFermat"
REF_DIR="out"
TOTAL_COUNT=0
CORRECT_COUNT=0

# Get list of files in output and reference directories
OUT_FILES=$(ls $OUT_DIR)
REF_FILES=$(ls $REF_DIR)

# Loop through each file in output directory
for FILE in $OUT_FILES
do
	# Get the test ID
	TEST_ID=${FILE%.out}
	
	# Check if the file exists in reference directory
	if [ -f "$REF_DIR/$TEST_ID.out" ]
	then
		# Compare the files
		DIFF=$(diff $OUT_DIR/$FILE $REF_DIR/$TEST_ID.out)
		
		# Increment total count
		TOTAL_COUNT=$((TOTAL_COUNT + 1))
		
		# Check if the files are identical
		if [ -z "$DIFF" ]
		then
			# If identical, increment correct count
			CORRECT_COUNT=$((CORRECT_COUNT + 1))
		fi
	fi
done

# Calculate accuracy
ACCURACY=$((CORRECT_COUNT * 100 / TOTAL_COUNT))

# Display result
echo "Total accuracy: $ACCURACY%"
