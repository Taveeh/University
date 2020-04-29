#!/bin/bash

# 4. Sort all files given as command line arguments descending by size.

n=0
while [ $# -gt 0 ]; do
	if [ -f "$1" ]; then
		echo "$(du "$1")"
		array[$n]="$(du  "$1")"
		n=$((n + 1))
	fi
	shift 1
done
echo "Read all"
n=$((n - 1))
for i in $(seq 0 $n); do
	aux="$aux"$'\n'"${array[i]}"
done
aux="${aux:1}"
echo "$aux" | sort -n

