#########################################################################
# File Name: color.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Thu 07 Jul 2016 04:23:10 PM CST
#########################################################################
#!/bin/bash
for i in {40..47};do
    for j in {30..37};do
        for k in 1 2 4 5 7 8 9 ;do
            echo -e " $i $j $k \e[${i};${j};${k}m hello world. \e[0m"
        done
        printf "\n\n"
    done
    printf "\n\n"
done |more
