/*************************************************************************
  > File Name: duffs_device.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Wed 30 Aug 2017 05:05:04 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/time.h>


void cp(char * to , char *from, int count) {
    int n = (count + 7) /8;

    switch (count % 8) {
        case 0: do { *to++ = *from++;
                    case 7:*to++ = *from++;
                    case 6:*to++ = *from++;
                    case 5:*to++ = *from++;
                    case 4:*to++ = *from++;
                    case 3:*to++ = *from++;
                    case 2:*to++ = *from++;
                    case 1:*to++ = *from++;
                } while(--n > 0);
    } //end switch
}

void ncp(char* to , char* from , int count) {
    for (int i = 0; i < count; ++i)
        *to++ = *from++;
}


int main(int argc, char* argv[])
{

    char src[] = {'1', '2','3','4','5','6','7','8','9','0','1', '2','3','4','5','6','7','8','9','0'};
    char dest1[8] = {0};
    char dest2[9] = {0};

    char dest3[8] = {0};
    char dest4[9] = {0};

    {
        
        struct timeval start1;
        struct timeval stop1;

        gettimeofday(&start1, NULL);
        for (int i = 0; i < 1000000; ++i) {
        ncp(dest3, src, sizeof(dest3) - 1);
        ncp(dest4, src, sizeof(dest4) - 1);
        }
        gettimeofday(&stop1, NULL);

        printf("%s\n", dest3);
        printf("%s\n", dest4);

        printf("norm eslapse: %ld s %ld us\n", stop1.tv_sec - start1.tv_sec, stop1.tv_usec - start1.tv_usec );
    }


    struct timeval start;
    struct timeval stop;

    gettimeofday(&start, NULL);

    for (int i = 0; i < 1000000; ++i) {
        cp(dest1, src, sizeof(dest1) - 1);
        cp(dest2, src, sizeof(dest2) - 1);
    }
    gettimeofday(&stop, NULL);

    printf("%s\n", dest2);
    printf("%s\n", dest1);

    printf("duffs device eslapse: %ld s %ld us\n", stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec );


    

    return 0;
}
