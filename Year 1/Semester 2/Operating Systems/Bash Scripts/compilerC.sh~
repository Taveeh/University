#!/usr/local/bin/bash

if [ $# -eq 0 ]; then
	echo "No source files" >& 2
	exit 1
fi
string=""

for file in $@; do
	string=$string" "$file
done
$(cat $string >  newFile.c)
exit 0
name=$(echo "$1" | awk -F. '{print $1}')
program="$name"".out"
echo " $(eval "gcc -Wall -g $string -o \"$program\"")"
echo $program
program="./""$program"
echo $program
echo "$(valgrind $program)"

