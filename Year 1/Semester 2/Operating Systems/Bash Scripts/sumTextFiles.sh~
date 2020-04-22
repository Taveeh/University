#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Please provide exactly one argument"
fi
sum=0
for F in $(ls "$1"); do
	if [ -f "$F" ]; then
		echo "$F"
		isFile=$(file "$F" | grep -c "text")
		if [ $isFile -eq 1 ]; then
			fileSize=$(stat -c%s "$F")
			sum=$((sum + fileSize))
		fi
	fi
done

echo "Total size: $sum"
