/*************************************************************************
    > File Name: ep_hello1.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 24 May 2017 12:09:15 PM CST
 ************************************************************************/

#include <unistd.h>
#include <iostream>
#include <sys/epoll.h>
using namespace std;
int main(int argc, char* argv[])
{
    int epfd,nfds;
    struct epoll_event ev,events[5];//ev用于注册事件，数组用于返回要处理的事件
    epfd=epoll_create(1);//只需要监听一个描述符——标准输入
    ev.data.fd=STDIN_FILENO;
    //ev.events=EPOLLIN|EPOLLET;//监听读状态同时设置ET模式
    ev.events=EPOLLIN;//监听读状态同时设置ET模式

    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&ev);//注册epoll事件
    for(;;)
   {
     nfds=epoll_wait(epfd,events,5,-1);

     for(int i=0;i<nfds;i++)
     {
        if(events[i].data.fd==STDIN_FILENO)
           cout<<"hello world!"<<endl;
     }
   }
}
