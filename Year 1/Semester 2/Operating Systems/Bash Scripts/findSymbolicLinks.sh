#!/bin/bash

#7. Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use option -L to test if a path is a symbolic link, and option -e to test if it exists (will return false if the target to which the link points does not exist) 

if [ $# -ne 1 ]; then
	echo "Provide exactly one argument" >&2
	exit 1
fi

if [ ! -d "$1" ]; then
	echo "Please provide a directory" >&2
	exit 1
fi

for link in $(find "$1" -type l); do
	if [ ! -e "$link" ]; then
		echo "$link points to an inexisting file"
	else
		echo "$link points to an existing file"
	fi
done

