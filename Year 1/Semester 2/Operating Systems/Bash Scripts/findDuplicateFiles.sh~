#!/usr/local/bin/bash

# Write a script that finds in a given directory hierarchy, all duplicate files and displays their paths. Hint: use checksums to detect whether two files are identical.

if [ $# -ne 1 ]; then
	echo "Please give one directory" >& 2
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Not a directory"
	exit 1
fi

declare -A fileArray
n=0
for file in $(find $1); do
	if [ -e $file ] && [ ! -d $file ]; then
		fileArray[$n]=$file
		n=$(($n + 1))
	fi
done

for file in ${fileArray[@]}; do
	for otherFile in ${fileArray[@]}; do
		checkFile=$(md5sum $file | awk '{print $1}')
		checkOtherFile=$(md5sum $otherFile | awk '{print $1}')
		if [ $file != $otherFile ] && [ $checkFile == $checkOtherFile ]; then
			echo "$file and $otherFile are the same"
		fi
	done
done

