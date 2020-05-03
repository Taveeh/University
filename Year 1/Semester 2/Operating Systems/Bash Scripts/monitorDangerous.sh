#!/usr/local/bin/bash

# Write a script that receives dangerous program names as command line arguments. The script will monitor all the processes in the system, and whenever a program known to be dangerous is run, the script will kill it and display a message.

if [ $# -eq 0 ]; then
	echo "Please give at least one program name" >& 2
	exit 1
fi

size=0
while true; do
	for file in $@; do
		if [ -f $file ]; then
			testRun=$(ps aux | grep "$file" | grep -v "grep\|monitorDangerous")
			echo $testRun
			if [ ! -z $testRun ]; then
				$(kill -9 $testRun)
				echo "Process killed"
			fi
		fi
	done
	exit 0
done

