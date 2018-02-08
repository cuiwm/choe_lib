#########################################################################
# File Name: lst_mem1.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Wed 13 Sep 2017 11:33:59 AM CST
#########################################################################
#!/bin/bash
#The following one-liner also provides information on total memory consumption by the current user.
#
#echo "------------------------------------" && mem=0 && while read -r rss comm ; do mbs=$((rss/1024)); mem=$((mbs + mem)); echo $mbs"MB - $comm"; done <<< "$(ps -u $USER -wo rss=,comm= --sort -rss)" && echo "------------------------------------" && echo $mem"MB: Memory used by user '$USER'"
#I have just listed all user processes sorted by the highest memory usage in MB like this:
#
#ps -u $USER -wo rss=,comm= --sort -rss | while read -r rss comm ; do echo $((rss/1024))"MB -" $comm; done
#You can use command= instead of comm= to show the full path process.
#
#The = just removes the column title

echo "------------------------------------" && mem=0 && while read -r rss comm ; do mbs=$((rss/1024)); mem=$((mbs + mem)); echo $mbs"MB - $comm"; done <<< "$(ps -u $USER -wo rss=,comm= --sort -rss)" && echo "------------------------------------" && echo $mem"MB: Memory used by user '$USER'"
