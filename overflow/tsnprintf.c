/*************************************************************************
    > File Name: tsnprintf.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Thu 22 Jun 2017 04:04:41 PM CST
 ************************************************************************/
//filetype=unix
//fileencoding=utf-8
//filetype=c
//
//
// 中国 utf8编码 是6bytes  
// 编码是 fileencoding来决定的
#include <stdio.h>

int main(int argc, char* argv[])
{
    char buf[4];
    printf("char buf[4] snprintf\n");
    int ret1 = snprintf(buf, sizeof(buf), "%s", "hello");
    int ret2 = snprintf(buf, sizeof(buf), "%s", "中国");
    printf("%s(%d) ret:%d %s(%d) ret:%d\n", "hello", sizeof("hello"), ret1, "中国", sizeof("中国"), ret2);

    return 0;
}
