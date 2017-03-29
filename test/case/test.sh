#########################################################################
# File Name: test.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Mon 07 Mar 2016 02:04:26 PM CST
#########################################################################
#!/bin/bash

#    curl "http://192.168.32.101:9502/add_user?sub_app_type=4097&user_account=1-33002&nick_name=元芳&public=1"
for ((i=1; i< 5000000000; i++))
do
#    echo $i
    curl "http://192.168.32.101:9502/add_user?sub_app_type=4097&user_account=1-33002&nick_name=元芳&public=1"
done
