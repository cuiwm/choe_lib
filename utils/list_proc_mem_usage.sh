#########################################################################
# File Name: list_proc_mem_usage.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Wed 13 Sep 2017 11:09:23 AM CST
#########################################################################
#!/bin/bash

#List processes by memory usage

#ps -e -orss=,args= | sort -b -k1,1n
ps -e -orss=,pid=,args= | sort -b -k1,1n
