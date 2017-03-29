/*************************************************************************
    > File Name: tplus.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Mon 20 Feb 2017 09:13:30 PM CST
 ************************************************************************/

#include <stdio.h>


int main(int argc, char* argv[])
{
	int a[5]={1,2,3,4,5};
	int *p=a;

	*p++=100;

	printf("p:%d\n", *p);
	*(p++)=101;
	printf("p:%d\n", *p);
    int i = 0;
    for (; i < 5; ++i) {
        printf(" %d:%d\n", i, a[i] );
    }
	return 0;
}
