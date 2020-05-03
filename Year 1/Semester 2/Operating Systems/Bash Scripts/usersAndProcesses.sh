#!/usr/local/bin/bash

# Display a report showing the full name of all the users currently connected, and the number of processes belonging to each of them.

declare -A user_name
user_name=$(cat utils/who.fake | awk '{print $1}')

for user in $user_name; do
	# $(cat utils/ps.fake | grep "^bradu" | wc -l)
	echo "$user $(cat utils/ps.fake | grep "^$user" | wc -l)"
done


