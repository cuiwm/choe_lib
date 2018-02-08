#########################################################################
# File Name: tps.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Wed 13 Sep 2017 11:06:18 AM CST
#########################################################################
#!/bin/bash
#
#down vote
#ps ef -o command,vsize,rss,%mem,size
#
#I could not find an option for shared memory, but I did find options for % of total physical memory and the amount of swapspace that would be needed to swap out the process. This and much more is documented in the man page for ps.
ps -efx -o command,vsize,rss,%mem,size 
