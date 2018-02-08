#########################################################################
# File Name: tsmaps.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Wed 13 Sep 2017 10:53:20 AM CST
#########################################################################
#!/bin/bash

#7 https://superuser.com/questions/102005/how-can-i-display-the-memory-usage-of-each-process-if-i-do-a-ps-ef?newreg=8e11db7e75df46e9ad0d3ecc5d3aa711
#down vote
#accepted
#Obtaining memory usage through ps is pretty unreliable. If you have a newer kernel it should support /proc/pid#/smaps which gives you some detailed information on each processes memory usage. Below is a pretty dirty and quick script to loop through each process that is open and grab the Size, Rss, Pss and Shared Clean/Dirty usage. Hopefully it can be useful in some kind of way.
#
#for pid in $(ps -ef | awk '{print $2}'); do
#    if [ -f /proc/$pid/smaps ]; then
#            echo "* Mem usage for PID $pid"
#            echo "-- Size:"
#            cat /proc/$pid/smaps | grep -m 1 -e ^Size: | awk '{print $2}'
#            echo "-- Rss:"
#            cat /proc/$pid/smaps | grep -m 1 -e ^Rss: | awk '{print $2}'
#            echo "-- Pss:"
#            cat /proc/$pid/smaps | grep -m 1 -e ^Pss: | awk '{print $2}'
#            echo "Shared Clean"
#            cat /proc/$pid/smaps | grep -m 1 -e '^Shared_Clean:' | awk '{print $2}'
#            echo "Shared Dirty"
#            cat /proc/$pid/smaps | grep -m 1 -e '^Shared Dirty:' | awk '{print $2}'
#    fi
#done
#er26528's answer doesn't quite calculate the memory correctly - you need the sum of the mappings in smaps, not just the top one. This script should do it:
#
##!/bin/bash
#
if [ -z $1 ] ; then
	echo `basename $0` process_name
	exit -1
fi

for pid in $(ps -ef | grep $1| awk '{print $2}'); do
    if [ -f /proc/$pid/smaps ]; then
        echo "* Mem usage for PID $pid"     
        rss=$(awk 'BEGIN {i=0} /^Rss/ {i = i + $2} END {print i}' /proc/$pid/smaps)
        pss=$(awk 'BEGIN {i=0} /^Pss/ {i = i + $2 + 0.5} END {print i}' /proc/$pid/smaps)
        sc=$(awk 'BEGIN {i=0} /^Shared_Clean/ {i = i + $2} END {print i}' /proc/$pid/smaps)            
        sd=$(awk 'BEGIN {i=0} /^Shared_Dirty/ {i = i + $2} END {print i}' /proc/$pid/smaps)
        pc=$(awk 'BEGIN {i=0} /^Private_Clean/ {i = i + $2} END {print i}' /proc/$pid/smaps)
        pd=$(awk 'BEGIN {i=0} /^Private_Dirty/ {i = i + $2} END {print i}' /proc/$pid/smaps)
        echo "-- Rss: $rss kB" 
        echo "-- Pss: $pss kB"
        echo "Shared Clean $sc kB"
        echo "Shared Dirty $sd kB"
        echo "Private $(($pd + $pc)) kB"
    fi
done

	
#Outputs: line 16: + : syntax error: operand expected (error token is "+ ") which is the line that contains: echo "Private $(($pd + $pc)) kB", I'm running on CentOS 7. – Basil A Jan 10 '16 at 17:19
#1	 	
#@BasilA - Thanks, fixed that – evsmith Jan 10 '16 at 23:17
#  	 	
#@evsmith why add 0.5 to Pss? – Pete Jun 23 at 4:01
