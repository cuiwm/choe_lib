/*************************************************************************
    > File Name: tasan1.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Fri 10 Mar 2017 07:56:22 PM CST
 ************************************************************************/

#include <stdio.h>

int *ptr;
__attribute__((noinline))
void FunctionThatEscapesLocalObject() {
  int local[100];
  ptr = &local[0];
}

int main(int argc, char **argv) {
  FunctionThatEscapesLocalObject();
  return ptr[argc];
}
