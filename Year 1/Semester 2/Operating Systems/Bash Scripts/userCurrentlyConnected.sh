#!/usr/local/bin/bash

# 1. Display a report showing the full name of all the users currently connected, and the number of processes belonging to each of them.

declare -A userArr

userArr=$(cat utils/who.fake | awk -f: '{print $1}') 
