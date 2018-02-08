#########################################################################
# File Name: case.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Wed 26 Jul 2017 11:37:32 AM CST
#########################################################################
#! /bin/bash  -x

set -x

echo "Is it morning? Please answer yes or no."
read YES_OR_NO
case "$YES_OR_NO" in
yes|y|Yes|YES)
  echo "Good Morning!";;
[nN]*)
  echo "Good Afternoon!";;
*)
  echo "Sorry, $YES_OR_NO not recognized. Enter yes or no."
  exit 1;;
esac


read INPUT

case "$INPUT" in
yes|y|YES)
    echo "yes";;
[nN]*)
    echo "no";;
*)
    echo "unk"
    exit 1;;
esac
exit 0

