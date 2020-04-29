#!/bin/bash
#3. Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

while [ $# -gt 0 ]; do
	file=$1
	word=$2
	if [ -f "$file" ]; then
		wordCount=$(grep -o "\<$word\>" "$file" | wc -w)
		if [ $wordCount -ge 3 ]; then
			echo "$file contains $word $wordCount times"
		fi
	fi
	shift 2
done	
