/*************************************************************************
  > File Name: tclock_gettime.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Wed 23 Mar 2016 10:17:57 AM CST
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <time.h>
int main()
{
    struct timespec time1 = {0, 0};
    struct timespec my_tm = {0, 0};
    clock_gettime(CLOCK_REALTIME, &time1);
    printf("CLOCK_REALTIME: %d, %d\n", time1.tv_sec, time1.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &time1);
    clock_gettime(CLOCK_MONOTONIC_RAW, &my_tm);

    printf("\nCLOCK_MONOTONIC:\t%d, %d\n", time1.tv_sec, time1.tv_nsec);
    printf("CLOCK_MONOTONIC_RAW:\t%d, %d\n\n", my_tm.tv_sec, my_tm.tv_nsec);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    printf("CLOCK_PROCESS_CPUTIME_ID: %d, %d\n", time1.tv_sec, time1.tv_nsec);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);
    printf("CLOCK_THREAD_CPUTIME_ID: %d, %d\n", time1.tv_sec, time1.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC_RAW, &my_tm);
    printf("CLOCK_MONOTONIC_RAW: \n%d, %d\n", my_tm.tv_sec, my_tm.tv_nsec);

    printf("time:\n%d\n", time(NULL));
    sleep(1);
}
