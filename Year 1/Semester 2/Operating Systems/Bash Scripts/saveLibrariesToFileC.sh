#!/bin/bash

# 5. Write a script that extracts from all the C source files given as command line arguments the included libraries and saves them in a file.

while [ $# -gt 0 ]; do
	if [ -f "$1" ]; then
		isCFile=$(file "$1" |  grep -c "c program text")
		if [ $isCFile -eq 1 ]; then
			libs="$libs"$'\n'"$(grep "#include" "$1")"
		fi
	fi
	shift 1
done
echo "$libs" | sort | uniq > libs
