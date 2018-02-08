#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVPORT 9527
#define MAXBUF 1024

int main(void)
{
	char buf[MAXBUF];
	struct sockaddr_in servaddr;
	int fd;
	int n, len;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	servaddr.sin_port = htons(SERVPORT);

	if( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	if(connect(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("connect");
		exit(1);
	}

	for(n = 0; n < 10; n++)
	{
		snprintf(buf, MAXBUF, "time %d", n);
		len = strlen(buf);
		if(write(fd, buf, len) != len)
		{
			printf("write error");
			close(fd);
			exit(1);
		}

	}

	close(fd);

	return 0;
}

