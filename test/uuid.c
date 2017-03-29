/*************************************************************************
    > File Name: uuid.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Thu 31 Mar 2016 07:13:13 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <uuid/uuid.h>
#include <string.h>

void puuid()
{
    char buf[64] ={0};
    uuid_t uuid;

typedef struct _GUID {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} GUID;
GUID guid;

    uuid_generate(uuid);
    

    for (int i =0;  i< 16; i++)
    snprintf(buf+2*i, sizeof(buf)-2*i, "%02X", uuid[i]);

    /*
    snprintf( buf,
            sizeof(buf),
            "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
            guid.Data1, guid.Data2, guid.Data3,
            guid.Data4[0], guid.Data4[1],
            guid.Data4[2], guid.Data4[3],
            guid.Data4[4], guid.Data4[5],
            guid.Data4[6], guid.Data4[7]);
            */

    printf("uuid %d:%s\n", strlen(buf), buf);

}

int main(int argc, char* argv[])
{

    puuid();
    return 0;
}
