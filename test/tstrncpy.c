/*************************************************************************
    > File Name: tstrncpy.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Tue 28 Feb 2017 12:21:43 PM CST
 ************************************************************************/

/* strncpy example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str1[]= "To be or not to be";
  char str2[40] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
  char str3[40]= {0x31};

  /* copy to sized buffer (overflow safe): */
  strncpy ( str2, str1, sizeof(str2) );

  /* partial copy (only 5 chars): */
  strncpy ( str3, str2, 5 );
  str3[5] = '\0';   /* null character manually added */

  puts (str1);
  puts (str2);
  puts (str3);

  return 0;
}
