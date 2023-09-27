#!/bin/bash

#getting the list of processes
 
threshold=50

#creating log file
logfile="cpu_usage_log.csv"
touch "$logfile"

#note down the current date and time for logging purpose

current_time=$(date "+%Y-%m-%d %H:%M:%S")

#get the list of processes sorted by cpu usage in descending order
list=$(ps -eo pid,%cpu,cmd --sort=-%cpu | awk -v thresh="$threshold"  'NR>1 && $2 >thresh')
echo "contents of the list"
echo "$list"
#iterate through the process
while read -r pid cpu_utilization  _; do
  #log the process information
echo "$pid,$current_time,$cpu_utilization%">>"$logfile"

#kill the process
kill -9 "$pid"
echo "killed process with PID $pid(CPU utilization :$cpu_utilization %)"
done <<< "$list"

