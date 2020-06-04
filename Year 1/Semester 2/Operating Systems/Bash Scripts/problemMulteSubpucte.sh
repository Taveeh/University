#!/usr/local/bin/bash

declare -A strings
n=0
ok=1
sum=0
cnt=0
listFiles=""
while read str; do
	for elem in "${strings[@]}"; do
		if [ $elem == $str ]; then
			ok=2
			break
		fi
	done
	if [ -d $str ]; then
		index=0
		for i in $(du $str | sort -rn | awk '{print $2}'); do
			if [ $(grep "\.c$" | wc -c) -eq 1 ] && [ $index -lt 3 ]; then
				echo $str
				index=$(($index + 1))
			fi
		done
	else
		isNumber=$(echo "$str" | grep "^[0-9]+$" -c)
		if [ $isNumber -eq 1 ]; then
			sum=$(($sum + $str))
		else
			if [ -f $str ]; then
				readPerm=$(ls -l $str | grep "^.r" -c)
				if [ $readPerm -eq 1 ]; then
					listFiles="$listFiles"$"\n"
					cnt=$(($cnt + 1))
				fi
			else
				if [ $(cat /etc/passwd | grep $str -c) -ne 0 ]; then
					break
				fi
			fi
		fi
	fi
	if [ $ok -eq 2 ]; then
		break
	fi
	strings[$n]=$str
	n=$(($n + 1))
done

