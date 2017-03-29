/*************************************************************************
    > File Name: zUtils.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Mon 20 Feb 2017 06:05:59 PM CST
 ************************************************************************/

#include <sys/types.h>
#include <string.h>
//#include <stdio.h>
#include "zUtils.h"

static const char Hex[] = "0123456789ABCDEF";

bool Byte2HexStr(u_int8_t* bytes, int byte_count, char* out, int len) 
{
	if (len -1 < (byte_count << 1)) return false;

	char* p = out;

	for (int i = 0; i < byte_count; ++ i){
		u_int8_t v = bytes[i];
		*(p++) = Hex[v >> 4];
		*(p++) = Hex[v & 0x0f];
	}

	*p = '\0';
	return true;
}

int HexChar2Int(char c)
{
	switch(c)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': case 'a': return 10;
		case 'B': case 'b': return 11;
		case 'C': case 'c': return 12;
		case 'D': case 'd': return 13;
		case 'E': case 'e': return 14;
		case 'F': case 'f': return 15;
	}
	return -1;
}

static int HexDigit2Int(char hex)
{
    if ('0' <= hex  && hex <= '9')
        return hex - '0';

    /* Force lowercase */
    hex |= 0x20;
    if ('a' <= hex && hex <= 'f')
        return 10 + hex - 'a';

    return -1;
}

bool HexStr2Byte(const char* str, u_int8_t* hex, int hex_len)
{
	bool flag = true;
    int len = strlen(str)/2;
	if (hex_len < len) return false;

    for( int i = 0; i < len; i++ )
    {
		int u = HexDigit2Int(*str++);
		if (u < 0) { 
			flag = false; 
			break;
		}
        hex[i] =  (u << 4);

		int v = HexDigit2Int(*str++);
		if (v < 0) { 
			flag = false; 
			break;
		}
        hex[i] += v;
    }
	return flag;
}

//bool HexStr2Byte(const std::string &inStr, unsigned char *outStr)
//{
//    size_t len = inStr.length();
//    for (size_t i = 0; i < len; i += 2) {
//        sscanf(inStr.c_str() + i, "%2hhx", outStr);
//        ++outStr;
//    }
//    return true;
//}
//
//int main (int argc, char** argv) {
//    u_int8_t  t1[] = {0xaa, 0xad, 0xba, 0x00, 0x01, 0x99, 0xbb, 0xcc, 0xdd, 0xff};
//    u_int8_t  w[32];
//
//    printf(" {0xaa, 0xad, 0xba, 0x00, 0x01, 0x99, 0xbb, 0xcc, 0xdd, 0xff} ");
//    char buff[256];
//    if( Byte2HexStr(t1, sizeof(t1)/sizeof(u_int8_t), buff, sizeof(buff)/sizeof(buff[0])) ) {
//        printf("OK\n%s\n", buff);
//    }
//    int j = 0;
//    if( HexStr2Byte(buff, w, sizeof(w)/sizeof(w[0]))) {
//
//        printf("OK\n%s\n", buff);
//        for ( ; j < 32; ++j ) {
//            printf("%02X", w[j]);
//        }
//        printf("\n");
//    }
//
//}
