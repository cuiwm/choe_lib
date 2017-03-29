/*************************************************************************
    > File Name: tmacro.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Tue 05 Apr 2016 06:10:44 PM CST
 ************************************************************************/

#include <stdio.h>

#define _STRING(x) #x
#define STRING(x) _STRING(x)
int main(int argc, char* argv[])
{

       char* pChar = STRING(__FILE__);
       printf("%s %s\n", pChar, __FILE__);
       printf("chXX %s\n", _STRING(__FILE__));
       return 0;
}
