#!/usr/local/bin/bash

# Find recursively in a directory, all the files that have write permissions for everyone. Display their names, and the permissions before and after removing the write permission for everybody. You will need to use chmod's symbolic permissions mode, instead of the octal mode we have used in class. The the chmod manual for details.

for file in $(find ./utils); do
	if [ -f "$file" ]; then
		hasWrite=$(ls -l "$file" | grep "^.\{8\}w.*" -c)
		if [ $hasWrite -eq 1 ]; then
			echo "$(ls -l "$file")"
			$(chmod o-w "$file")
			echo "$(ls -l "$file")"
			$(chmod o+w "$file")
		fi
	fi
done

