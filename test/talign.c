/*************************************************************************
    > File Name: talign.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Sat 03 Sep 2016 02:44:08 PM CST
 ************************************************************************/

#include <stdio.h>

struct C
{
    char b;
    int a;
    short c;
};

#pragma pack(1)
struct D
{
    char b;
    int a;
    short c;
};
#pragma pack()

#pragma pack(2)
struct E
{
    char b;
    int a;
    short c;
};
#pragma pack()

struct F
{
    char b;
    int a;
    short c;
} __attribute__((__packed__));

struct G1 {
    char b;
    int a;
    short c;
} __attribute__((__aligned__(1)));

struct G2 {
    char b;
    int a;
    short c;
} __attribute__((__aligned__(2)));


struct G4 {
    char b;
    int a;
    short c;
} __attribute__((__aligned__(4)));

typedef struct G4 G4A;

int main(int argc, char* argv[])
{
    printf("sizeof:%u\n", sizeof(struct C));
    printf("sizeof:%u\n", sizeof(struct D));
    printf("sizeof:%u\n", sizeof(struct E));
    printf("F sizeof:%u\n", sizeof(struct F));
    printf("G1 sizeof:%u\n", sizeof(struct G1));
    printf("G2 sizeof:%u\n", sizeof(struct G2));
    printf("G4 sizeof:%u\n", sizeof(struct G4));
    printf("G4 sizeof:%u\n", sizeof(G4A));
return 0;
}
