/*************************************************************************
  > File Name: tepoll.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Fri 18 Mar 2016 08:08:47 PM CST
 ************************************************************************/

#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <errno.h> 
#include <syslog.h>
#include <sys/time.h>

#define __USE_MISC 1
#include <netinet/tcp.h>

#define MAX_EVENTS 10
#define PORT 8084



/* Decode TCP options to string description. Please note that using strcat()
 * is highly dangerous and make sure you don't do it and never overwrite
 * your buffers! We use it here because we concatenate strings under our
 * control.
 */
void decode_tcp_options(char *options_text, u_int8_t tcp_options) {
    if ( (tcp_options & TCPI_OPT_TIMESTAMPS) ) {
        strcat(options_text, "Timestamps ");
    }
    if ( (tcp_options & TCPI_OPT_SACK) ) {
        strcat(options_text, "SACK ");
    }
    if ( (tcp_options & TCPI_OPT_WSCALE) ) {
        strcat(options_text, "Window Scaling ");
    }
    if ( (tcp_options & TCPI_OPT_ECN) ) {
        strcat(options_text, "ECN ");
    }
    return;
}

//设置socket连接为非阻塞模式
void setnonblocking(int sockfd) 
{    
    int opts;    
    opts = fcntl(sockfd, F_GETFL);    
    if(opts < 0) 
    {   
        perror("fcntl(F_GETFL)\n");     
        exit(1);    
    } 

    opts = (opts | O_NONBLOCK);  
    if(fcntl(sockfd, F_SETFL, opts) < 0) 
    {    
        perror("fcntl(F_SETFL)\n");     
        exit(1);    
    }
}


/* Get current time. */
void get_now( struct timeval *time, unsigned short debug ) {
    if ( gettimeofday( time, NULL ) != 0 ) {
        if ( debug > 0 ) {
            fprintf(stderr,"Can't get current time.\n");
        }
        else {
            syslog( LOG_DAEMON | LOG_INFO, "gettimeofday() failed. Can't get current time." );
        }
    }
    return;
}

/* Convert "struct timeval" to fractional seconds. */
double time_to_seconds ( struct timeval *tstart, struct timeval *tfinish ) {
    double t;

    t = (tfinish->tv_sec - tstart->tv_sec) + (tfinish->tv_usec - tstart->tv_usec) / 1e6;
    return t;
}

/* Get file size from file descriptor */
unsigned int get_filesize( int fd ) {
    struct stat s;

    if ( fstat( fd, &s ) == 0 ) {
        return(s.st_size);
    }
    else {
        return(0);
    }
}

int stat_update (int sockfd, FILE* statistics, struct timeval* time_start, short int opt_debug )
{
	//  if ( opt_debug > 0 ) {
	//      printf("\nReceived %d bytes on socket.\n",recv_bytes);
	//  }
	/* Measure time in order to create time intervals. */
	struct timeval time_fin;
	get_now( &time_fin, opt_debug );

	struct tcp_info tcp_info;
	/* Fill tcp_info structure with data */
	socklen_t tcp_info_length = sizeof(tcp_info);
	if ( getsockopt(sockfd, SOL_TCP, TCP_INFO, (void *)&tcp_info, (socklen_t *)&tcp_info_length ) == 0 ) {
		if ( opt_debug > 0 ) {
			printf("snd_cwnd: %u\nsnd_ssthresh: %u\nrcv_ssthresh: %u\nrtt: %u\nrtt_var: %u\n",
					tcp_info.tcpi_snd_cwnd,
					tcp_info.tcpi_snd_ssthresh,
					tcp_info.tcpi_rcv_ssthresh,
					tcp_info.tcpi_rtt,
					tcp_info.tcpi_rttvar
				  );
		}
		fprintf(statistics,"%.6f %u %u %u %u %u %u %u %u %u %u %u %u\n",
				time_to_seconds( time_start, &time_fin ),
				tcp_info.tcpi_last_data_sent,
				tcp_info.tcpi_last_data_recv,
				tcp_info.tcpi_snd_cwnd,
				tcp_info.tcpi_snd_ssthresh,
				tcp_info.tcpi_rcv_ssthresh,
				tcp_info.tcpi_rtt,
				tcp_info.tcpi_rttvar,
				tcp_info.tcpi_unacked,
				tcp_info.tcpi_sacked,
				tcp_info.tcpi_lost,
				tcp_info.tcpi_retrans,
				tcp_info.tcpi_fackets
			   );
		if ( fflush(statistics) != 0 ) {
			if ( opt_debug > 0 ) {
				fprintf(stderr, "Cannot flush buffers: %s\n", strerror(errno) );
			}
			else {
				syslog( LOG_DAEMON | LOG_CRIT, "Cannot flush buffers: %s", strerror(errno) );
			}
		}
	}
}

FILE *statistics;
char my_buf[300*1024]={0};

int main()
{ 


	struct tcp_info tcp_info;
	/* Structures needed for measuring time intervals */
struct timeval time_start, time_now, time_delta;
#define MAX_TCPOPT          256
    static char tcp_options_text[MAX_TCPOPT];
    unsigned short opt_debug = 0;
    struct epoll_event ev, events[MAX_EVENTS];   
    int addrlen, listenfd, conn_sock, nfds, epfd, fd, i, nread, n, nidx, paused = 0;  
    struct sockaddr_in local, remote;  
    char buf[BUFSIZ];   
    char *my_ptr = my_buf;

    openlog("choe-send", LOG_PID, LOG_DAEMON );
    statistics = fopen("/tmp/tsend.log" , "a+" );
    if ( statistics == NULL ) {
        if ( opt_debug > 0 ) {
            fprintf(stderr,"Could not open statistics file: %s\n",strerror(errno));
        }
        else {
            syslog( LOG_DAEMON | LOG_CRIT, "Could not open statistics file: %s", strerror(errno) );
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < sizeof(my_buf)/sizeof(char)-1; i++)
    {
        *my_ptr++ = 0x30 + i % 10;
    }

    printf("len:%d \n", strlen(my_buf));

    //创建listen socket   
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {   
        perror("sockfd\n");     
        exit(1);    
    } 

    setnonblocking(listenfd);   

    bzero(&local, sizeof(local));  
    local.sin_family = AF_INET;  
    local.sin_addr.s_addr = htonl(INADDR_ANY); 
    local.sin_port = htons(PORT);  
    if( bind(listenfd, (struct sockaddr *) &local, sizeof(local)) < 0) 
    {    
        perror("bind\n");     
        exit(1);    
    } 
    listen(listenfd, 20);  
    epfd = epoll_create(MAX_EVENTS);  
    if (epfd == -1) 
    {      
        perror("epoll_create");  
        exit(EXIT_FAILURE);    
    }   
    ev.events = EPOLLIN; 
    ev.data.fd = listenfd; 
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) 
    {      
        perror("epoll_ctl: listen_sock");     
        exit(EXIT_FAILURE);    
    }  

    for (;;) 
    {      
        nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);   
		printf("epoll_wait ret:%d\n", nfds);
        if (nfds == -1) 
        {         
            perror("epoll_pwait");   
            exit(EXIT_FAILURE);        
        }      
        for (i = 0; i < nfds; ++i) 
        {         
            fd = events[i].data.fd;      

			printf("loop: fd: %d epoll_wait ret:%d \n", fd, nfds);
            if (fd == listenfd) 
            {               
                while ((conn_sock = accept(listenfd,(struct sockaddr *) &remote, (socklen_t *)&addrlen)) > 0) 
                {                
                    setnonblocking(conn_sock);               
                    ev.events = EPOLLIN | EPOLLOUT | EPOLLET;             
                    ev.data.fd = conn_sock;                
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) 
                    {                
                        perror("epoll_ctl: add");                     
                        exit(EXIT_FAILURE);                    
                    }                

					if ( opt_debug > 0 ) {
						printf("Got a new connection from client %s.\n",inet_ntoa(remote.sin_addr));
					}
					else {
						syslog( LOG_DAEMON | LOG_INFO, "Received connection from client at address %s.",
								inet_ntoa(remote.sin_addr));
					}

					/* Get time for counting milliseconds. */
					get_now( &time_start, opt_debug );

					/* Fill tcp_info structure with data to get the TCP options and the client's * name.  */
					socklen_t tcp_info_length = sizeof(tcp_info);
					if ( getsockopt( fd, SOL_IP, TCP_INFO, (void *)&tcp_info, (socklen_t *)&tcp_info_length ) == 0 ) {
						memset((void *)tcp_options_text, 0, MAX_TCPOPT);
						decode_tcp_options(tcp_options_text,tcp_info.tcpi_options);

						/* Write some statistics and start of connection to log file. */
						fprintf(statistics,"# Received connection from %s (AdvMSS %u, PMTU %u, options (%0.X): %s)\n",
								inet_ntoa(remote.sin_addr),
								tcp_info.tcpi_advmss,
								tcp_info.tcpi_pmtu,
								tcp_info.tcpi_options,
								tcp_options_text
							   );
					}
				}//end while              

				if (conn_sock == -1) 
				{                 
                    if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)               
                        perror("accept");                
                }               
                continue;            
            }//end if (fd == listenfd)             

			//work socket has a read event
            if (events[i].events & EPOLLIN) 
            {             
				printf("handle EPOLLIN\n");
                int n = 0;           
                while ((nread = read(fd, buf + n, BUFSIZ-1)) > 0) 
                {              
                    n += nread;                
                }          
                if (nread == -1 && errno != EAGAIN) 
                {    
                    perror("read error");                
                }              
                ev.data.fd = fd;            
                ev.events = events[i].events | EPOLLOUT;         
                if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) 
                {               
                    perror("epoll_ctl: mod");                
                }            
            }//end if (events[i] ...         

			//work soket has a write event
            if (events[i].events & EPOLLOUT) 
            {              
                sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);         
                //int nwrite, data_size = strlen(buf);            
                int nwrite, data_size = strlen(my_buf);            
				if (!paused) {
					n = data_size;         

				} //begin time

				printf("\n>>>>可写信号before while left :(%d) date_size:%d\n", n, data_size);
				int i = 1;
				while (n > 0) 
				{                  
					//nwrite = write(fd, buf + data_size - n, n);                

					nwrite = write(fd, my_buf + data_size - n, n);                
					printf("\n[%d]write count:%d left:%d\n", i++, nwrite, n);

					stat_update (fd, statistics, &time_start, 1 );
					if (nwrite == -1) { //error
						if (errno == EINTR) {
							printf("EINTR\n");
							continue;
						} else if (errno == EAGAIN) {
							printf("EAGAIN\n");
						} else {
							printf("errno:%d\n", errno);
						}

						break;

					} else if (nwrite < n) {                      

                        if (nwrite == -1 && errno != EAGAIN) 
                        {                         
                            perror("write error");                        
							break;                    
                        }                    
                    }               
                    n -= nwrite;                

					printf("\nin  while step left :(%d) date_size:%d\n", n, data_size);
                }            
  
				printf("\n<<<<<after while left :(%d) expect_send_date_size:%d\n", n, data_size);
				if (n < 1) {
					paused = 0;
					printf("close fd:%d\n", fd);	
					close(fd);            
				}
				else
					paused = 1;

            }        
        }    
    }//end for (;;)   

    //free(tcp_buffer);
    fclose(statistics);
    //close(tcp_socket);
    closelog();

    return 0;
}
