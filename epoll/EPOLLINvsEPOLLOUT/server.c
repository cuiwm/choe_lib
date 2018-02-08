#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>


#define SERVPORT 9527
#define MAXBUF 1024
#define MAXFDS 5000
#define EVENTSIZE 100


ssize_t readn(int fd, void *vptr, size_t n)
{
	char *ptr;
	size_t nleft;
	ssize_t nread;

	nleft = n;
	ptr = vptr;
	while(nleft > 0)
	{
		if( (nread = read(fd, ptr, nleft)) == -1)
		{
			if(errno == EINTR)
				continue;
			else if(errno == EAGAIN)
				break;
			else
				return (-1);

		}
		else if(nread == 0)
			break;

		nleft -= nread;
		ptr += nread;
	}

	return (n - nleft);
}

int setnonblocking(int fd)
{
	int opts;
	if( (opts = fcntl(fd, F_GETFL, 0)) == -1)
	{
		perror("fcntl");
		return -1;
	}

	opts = opts | O_NONBLOCK;
	if( (opts = fcntl(fd, F_SETFL, opts)) == -1)
	{
		perror("fcntl");
		return -1;
	}

	return 0;
}

int main(void)
{
	char buf[MAXBUF];
	int len, n;

	struct sockaddr_in servaddr;
	int sockfd, listenfd, epollfd, nfds;

	struct epoll_event ev;
	struct epoll_event events[EVENTSIZE];

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVPORT);

	if( (epollfd = epoll_create(MAXFDS)) == -1)
	{
		perror("epoll");
		exit(1);
	}

	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	if(setnonblocking(listenfd) == -1)
	{
		perror("setnonblocking");
		exit(1);
	}

	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if(listen(listenfd, 10) == -1)
	{
		perror("listen");
		exit(1);
	}


	/* --------------------------------------------*/
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = listenfd;
	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
	{
		perror("epoll_ctl");
		exit(1);
	}

	for( ; ; )
	{
		if( (nfds = epoll_wait(epollfd, events, EVENTSIZE, -1)) == -1)
		{
			perror("epoll_wait");
			exit(1);
		}

		for(n = 0; n < nfds; n++)
		{
			if(events[n].data.fd == listenfd)
			{
				while( (sockfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) > 0)
				{
					if(setnonblocking(sockfd) == -1)
					{
						perror("setnonblocking");
						exit(1);
					}
					ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
					ev.data.fd = sockfd;
					if(epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1)
					{
						perror("epoll_ctl");
						exit(1);
					}
				}
				/*if(sockfd == -1)
				  {
				  perror("accept");
				  exit(1);
				  }*/
			}
			else
			{
				if(events[n].events & EPOLLIN)
				{
					if( (len = readn(events[n].data.fd, buf, MAXBUF)) == -1)
					{
						perror("readn");
						exit(1);
					}
					else if(len == 0)
					{
						close(events[n].data.fd);
						ev.data.fd = events[n].data.fd;
						epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
					}

					buf[len] = '\0';
					printf("received %s\n", buf);
				}

				if(events[n].events & EPOLLOUT)
				{
					printf("when EPOLLIN is triggered, EPOLLOUT is also triggered\n");
				}
			}
		}
	}
}

