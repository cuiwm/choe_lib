/*************************************************************************
  > File Name: choe_copy.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Fri 05 Feb 2016 12:21:05 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/times.h>

#define error(fmt,args...) \
    printf(fmt, ##args) ; \
printf(":%s\n",strerror(errno))

inline int cp_rw(int srcfd,int dstfd,char *buf,int len);
inline int cp_map(int srcfd,int dstfd,size_t len);

int main(int argc,char **argv)
{
    char buf[8192];
    int srcfd,dstfd;
    clock_t start,end;
    struct tms stm,ntm;
    struct stat filestat;
    int tck;
    char cmdline[30];

    if(argc!=3)
    {
        printf("usage: cmd <src> <dst>");
        exit(20);
    }
    tck=sysconf(_SC_CLK_TCK);


    start = times(&stm);
    if((srcfd=open(argv[1],O_RDONLY))==-1)
    {
        error("open %s error",argv[1]);
        exit(0);
    }
    if((dstfd=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666))==-1)
    {
        error("creat %s error",argv[2]);
        exit(0);
    }

    fstat(srcfd,&filestat);
    if(lseek(dstfd,filestat.st_size,SEEK_SET)==-1)
    {
        error("lseek error");
        exit(0);
    }
    if(write(dstfd," ",1)!=1)
    {
        error("write error");
        exit(0);
    }
    cp_map(srcfd,dstfd,filestat.st_size);
    close(srcfd);
    close(dstfd);
    end = times(&ntm);
    printf("copying %s to %s using cp_map:filesize=%lu MBytes Using %f seconds\n"
            ,argv[1],argv[2],filestat.st_size>>20,(end-start)/(double)tck); 

    sprintf(cmdline,"rm -f %s",argv[2]);
    system(cmdline);


    start = times(&stm);
    if((srcfd=open(argv[1],O_RDONLY))==-1)
    {
        error("open %s error",argv[1]);
    }
    if((dstfd=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666))==-1)
    {
        error("creat %s error",argv[2]);
    }
    cp_rw(srcfd,dstfd,buf,sizeof(buf));
    fstat(srcfd,&filestat);
    close(srcfd);
    close(dstfd);
    end = times(&ntm);
    printf("copying %s to %s using cp_rw:filesize=%lu MBytes Using %f seconds\n"
            ,argv[1],argv[2],filestat.st_size>>20,(end-start)/(double)tck);



    return 0;
}

inline int cp_rw(int srcfd,int dstfd,char *buf,int len)
{
    int nread;
    while((nread=read(srcfd,buf,len))>0)
    {
        if(write(dstfd,buf,nread)!=nread)
        {
            error("write error");
            return -1;
        }
    }
    if(nread ==-1)
    {
        error("read error");
        return -1;
    }
    return 0;
}

inline int cp_map(int srcfd,int dstfd,size_t len)
{
    char *src,*dst;
    if((src=mmap(0,len,PROT_READ,MAP_SHARED,srcfd,0))==MAP_FAILED)
    {
        error("mmap src error");
        return -1;
    }
    if((dst=mmap(0,len,PROT_WRITE,MAP_SHARED,dstfd,0))==MAP_FAILED)
    {
        error("mmap dst error");
        return -1;
    }
    if(memcpy(dst,src,len)==NULL)
    {
        error("memcpy error");
        return -1;
    }
    munmap(src,len);
    munmap(dst,len);
    return 0;
}
