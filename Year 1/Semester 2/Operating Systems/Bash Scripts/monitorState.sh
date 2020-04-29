#!/bin/bash

#6. Seminar problem: Write a script that monitors the state of a given folder and prints a message when something changed.

folder=$1
if [ -z "$folder" ]; then
	echo "No directory provided" >&2
	exit 1
fi

if [ ! -d "$folder" ]; then
	echo "Directory $folder does not exist" >&2
	exit 1
fi

OLD_STATE=""
while true; do
	STATE=""
	for P in $(find $folder); do
		if [ -f "$P" ]; then
			props=$(ls -l "$P" | sha256sum)
			content=$(sha256sum "$P")
		elif [ -d "$P" ]; then
			props=$(ls -ld "$P" | sha256sum)
			content=$(ls -l "$P" | sha256sum)
		fi
		STATE="$STATE"$'\n'"$props $content"
	done
	if [ -n "$OLD_STATE" ]; then
		if [ "$OLD_STATE" != "$STATE" ]; then
			echo "Directory state changed"
		fi
	fi
	OLD_STATE=$STATE
	sleep 1
done

