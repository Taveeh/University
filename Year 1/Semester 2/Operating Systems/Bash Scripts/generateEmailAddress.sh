#!/usr/local/bin/bash

# 7. Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma.
if [ ! $# -eq 1 ]; then
	echo "Invalid parameters" >& 2
	exit 1
fi

if [ -z "$1" ]; then
	echo "Invalid file" >& 2
	exit 1
fi

file=$(cat "$1" | awk '{print $1}')
first=0
echo "$file"
stringMail=""
while read userName; do
	if [ ! $first -eq 0 ]; then
		stringMail="${stringMail},"
	fi
	stringMail="${stringMail}""$userName""@scs.ubbcluj.ro"
	first=$(($first + 1))
done <<< "$file"

echo "$stringMail"
