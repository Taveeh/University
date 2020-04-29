#!/usr/local/bin/bash

#9. Calculate the average of all process ids in the system per user. 

user_pids=$(ps -ef | awk 'NR > 1{print $1" "$2}')

declare -A user_count
declare -A pid_sum
while read user pid; do
	user_count[$user]=$((user_count[$user] + 1))
	pid_sum[$user]=$((pid_sum[$user] + $pid))
done <<< "$user_pids"

for user in "${!user_count[@]}"; do
	echo "$user ---------- $((pid_sum[$user] / user_count[$user]))"
done

