/*************************************************************************
  > File Name: getIPInfo.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Mon 08 May 2017 05:48:15 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{ 
	int fd; 
	struct ifreq ifr; 
	fd = socket(AF_INET, SOCK_DGRAM, 0); /* I want to get an IPv4 IP address */ 
	ifr.ifr_addr.sa_family = AF_INET; /* I want IP address attached to "eth0" */ 
	strncpy(ifr.ifr_name, "eth1", IFNAMSIZ-1); 

	ioctl(fd, SIOCGIFADDR, &ifr); 
	close(fd); /* display result */ 

	printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr)); 
	return 0;
}
