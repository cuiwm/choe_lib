/*************************************************************************
    > File Name: debug_macro.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Tue 06 Jun 2017 03:10:44 PM CST
 ************************************************************************/

#include <stdio.h>
#include "debug_macro.h"

#define M 42
#define ADD(x) (M + x)
#define A2(x)  do { \
    int a =  (M + x); \
    printf("macro:a: %d", a);\
} while(0)

int main ()
{
#define N 28
  printf ("Hello, world!\n");
#undef N
  printf ("We're so creative.\n");
#define N 1729
  printf ("Goodbye, world!\n");
  A2(5);

  return 0;
  
}
