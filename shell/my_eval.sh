#########################################################################
# File Name: my_eval.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Mon 24 Jul 2017 11:27:12 AM CST
#########################################################################

#!/bin/bash
v1=aaa 
v2=bbb 
c=1

if [ $c -eq 1 ]   #整数比较
then 
    vname=v$c #找到符合条件的变量名为v1 
    eval vvv="$"$vname ; echo vvv: $vvv #将变量v1的值赋予vvv,即,使vvv=aaa 
    eval vvv='$'$vname ; echo vvv: $vvv #将变量v1的值赋予vvv,即,使vvv=aaa 
    eval vvv=\$$vname ; echo vvv: $vvv # 
    eval vvv=$$vname ; echo vvv: $vvv #错误用法 
fi
