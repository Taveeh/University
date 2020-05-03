#!/usr/local/bin/bash

# Find recursively in a directory, all the files with the extension ".log" and sort their lines (replace the original file with the sorted content)

for file in $(find utils/dir | grep "\.log$"); do
	echo $(cat "$file" | sort) >& "$file"
done

