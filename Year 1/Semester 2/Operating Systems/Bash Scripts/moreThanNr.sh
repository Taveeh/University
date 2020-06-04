#!/usr/local/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid arguments" >& 2
	exit 1
fi

echo "" > report.txt

number=$1
shift 1
for file in $@; do
	if [ -d $file ]; then
		nrFiles=$(ls -l $file | grep "^d" | wc -l)
		if [ $nrFiles -ge $number ]; then
			echo "$file" >> report.txt
		fi
	elif [ -f $file ]; then
		nrLines=$(cat $file | wc -l)
		if [ $nrLines -ge $number ]; then
			echo "$file"
		fi
	fi
done

