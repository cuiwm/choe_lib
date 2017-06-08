/*************************************************************************
    > File Name: getAllIP.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Mon 08 May 2017 06:10:16 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
 
int main (int argc, const char * argv[]) {
	struct ifaddrs * ifAddrStruct=NULL;
	void * tmpAddrPtr=NULL;
 
	getifaddrs(&ifAddrStruct);
 
	while (ifAddrStruct!=NULL) {
		if (ifAddrStruct->ifa_addr->sa_family==AF_INET) { // check it is IP4
 
			// is a valid IP4 Address
			tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
 
			// Netmask
			tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_netmask)->sin_addr;
			char netmaskBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, netmaskBuffer, INET_ADDRSTRLEN);
 
			// Broadcast
			tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_broadaddr)->sin_addr;
			char broadaddrBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, broadaddrBuffer, INET_ADDRSTRLEN);
 
			printf("%s IP Address %s Netmask %s Broadcast %s\n", ifAddrStruct->ifa_name, addressBuffer, netmaskBuffer, broadaddrBuffer); 
 
		} else if (ifAddrStruct->ifa_addr->sa_family==AF_INET6) { // check it is IP6
 
			// is a valid IP6 Address
			tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
			char addressBuffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
			printf("%s IP Address %s\n", ifAddrStruct->ifa_name, addressBuffer); 
 
		} 
 
		ifAddrStruct=ifAddrStruct->ifa_next;
	}
	return 0;
}
