#!/usr/local/bin/bash

# Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files.

nrFound=0
for file in $(find utils/dir | grep "\.c$"); do
	nrLines=$(cat "$file" | wc -l)
	if [ $nrLines -gt 500 ]; then
		nrFound=$(($nrFound + 1))
		echo "$file"
	fi
	if [ $nrFound -eq 2 ]; then
		exit 0
	fi
done

