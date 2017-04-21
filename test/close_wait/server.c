/*************************************************************************
  > File Name: server.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Fri 21 Apr 2017 02:46:43 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <errno.h>


#define MAXLINE 80
#define SERV_PORT 8000


static int
make_socket_non_blocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}

static int
create_and_bind (char *port)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s, sfd;

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
  hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
  hints.ai_flags = AI_PASSIVE;     /* All interfaces */

  s = getaddrinfo (NULL, port, &hints, &result);
  if (s != 0)
    {
      fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
      return -1;
    }

  for (rp = result; rp != NULL; rp = rp->ai_next)
    {
      sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
      if (sfd == -1)
        continue;

      s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
      if (s == 0)
        {
          /* We managed to bind successfully! */
          break;
        }

      close (sfd);
    }

  if (rp == NULL)
    {
      fprintf (stderr, "Could not bind\n");
      return -1;
    }

  freeaddrinfo (result);

  return sfd;
}
int gi = 0;

#define EP_STR "EPOLLIN = 0x001, \ 
    EPOLLPRI = 0x002, \
    EPOLLOUT = 0x004, \
    EPOLLRDNORM = 0x040, \
    EPOLLRDBAND = 0x080,\
    EPOLLWRNORM = 0x100,\
    EPOLLWRBAND = 0x200,\
    EPOLLMSG = 0x400,   \
    EPOLLERR = 0x008,   \
    EPOLLHUP = 0x010,   \
    EPOLLRDHUP = 0x2000,\
    EPOLLONESHOT = (1 << 30),   \
    EPOLLET = (1 << 31)\n"         

int main(int argc, char* argv[])
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    printf(EP_STR);
    //int i, n;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 20);

    int cc = make_socket_non_blocking (listenfd);
    if (cc < 0) {
        perror("noblock");
        abort();
    }
    printf("Accepting connections ...\n");
    int epfd = epoll_create1(0);
    if (epfd < 0)
    {
        printf("epoll_create1 fail.");
        abort();
    }

    struct epoll_event event;
    event.data.fd = listenfd;
    event.events = EPOLLIN|EPOLLET;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);
    if (ret < 0) {
        perror("epoll_ctl");
        abort();
    }

#define MAX_EVENTS  32
    /* Buffer where events are returned */
    struct epoll_event* events = calloc(MAX_EVENTS, sizeof event);

    while (1) {
        int n, i;
        printf("[%d]before epoll_wait\n", gi++);
        n = epoll_wait(epfd, events, MAX_EVENTS, -1);
        printf("[%d]after epoll_wait: n:%d\n", gi++, n);

        for (i = 0; i < n; ++i) {

            printf("\n[%d]sock:%d event:%x\n", gi++,  events[i].data.fd, events[i].events);

            if ( (events[i].events & EPOLLERR) ||
                    (events[i].events & EPOLLHUP) ||
                    (!(events[i].events & EPOLLIN)) )
            {
                fprintf(stderr, EP_STR);

                if  (events[i].events & EPOLLERR) {
                    fprintf(stderr, "~EPOLLERR~");
                }

                if (events[i].events & EPOLLHUP)  {
                    fprintf(stderr, "~EPOLLHUP~");
                }

                if (events[i].events & EPOLLRDHUP)  {
                    fprintf(stderr, "~EPOLLRDHUP~");
                }
                /*An error has occured on this fd, or the socket is 
                 * not ready for reading (why were we notified then?)*/
                fprintf(stderr, "########epoll error\n");
                close(events[i].data.fd);
                continue;
            }
            else if (listenfd == events[i].data.fd) {
                ///one or more incoming connections

                while (1) { 
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    char  hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                    in_len = sizeof in_addr;
                    int infd = accept(listenfd, &in_addr, &in_len);
                    if (infd == -1) {
                        if ( (errno == EAGAIN) ||
                                (errno == EWOULDBLOCK) )
                        {
                            break;
                        } else { 
                            perror("accept");
                            break;
                        }
                    } //end error

                    int s = getnameinfo(&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
                    if (s == 0) {
                        
                      printf("Accepted connection on descriptor %d "
                             "(host=%s, port=%s)\n", infd, hbuf, sbuf);

                    }//end if (s== 0



                  /* Make the incoming socket non-blocking and add it to the list of fds to monitor. */
                    
                  s = make_socket_non_blocking (infd);
                  if (s == -1)
                    abort ();

                  event.data.fd = infd;
                  event.events = EPOLLIN |EPOLLRDHUP| EPOLLET;
                  s = epoll_ctl(epfd, EPOLL_CTL_ADD, infd, &event);
                  if (s == -1 ) {
                      perror("epoll_ctl");
                      abort();
                  }


                } //end while
                
                continue;

            }
            else
            {
                /* We have data on the fd waiting to be read. 
                 * Read and display it.  We must read whatever data
                 * is available completely, as we are runing in 
                 * edge-triggered mode and won't get a notification
                 * again for the same data.*/
                int done = 0;

                while (1) {
                    ssize_t count;
                    char buf[512];

                    count = read(events[i].data.fd, buf, sizeof(buf)); 
                    printf("\n[%d]client socket read return %d\n", gi++, count);
                    if (count == -1) {
                        if (errno != EAGAIN) {
                            perror("read");
                            done = 1;
                        }

                        break;
                    } else if (count == 0) {
                        /*End of file. peer close the socket */
                        done = 1;
                        break;
                    }

                    int s = write(events[i].data.fd, buf, count);
                    if (s < 0) {
                        perror("write");
                        abort();
                    }

                }//end while (1)

                if (done) {
                    printf("Closed connection on descripor %d\n", events[i].data.fd);
                    /*Closing the descriptor will make epoll remove it 
                     * from the set of descriptors which are monitored*/
                    //close(events[i].data.fd);
                }

            } //end else..
            
        } //end for ..


     //   cliaddr_len = sizeof(cliaddr);
     //   printf("before accept() ...\n");
     //   connfd = accept(listenfd,
     //           (struct sockaddr *)&cliaddr, &cliaddr_len);
     //   printf("Accepted a new connections ...\n");
     //   //while (1)
     //   {
     //       n = read(connfd, buf, MAXLINE);
     //       if (n == 0) {
     //           printf("the other side has been closed.\n");
     //           break;
     //       }
     //       printf("received from %s at PORT %d\n",
     //               inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
     //               ntohs(cliaddr.sin_port));

     //       for (i = 0; i < n; i++)
     //           buf[i] = toupper(buf[i]);
     //       write(connfd, buf, n);
     //   }
     //   //这里故意不关闭socket,或者是在close之前加上一个sleep都可以
     //   //sleep(5);
        //close(connfd);
    } //while (1)

    free(events);
    close(epfd);
    return EXIT_SUCCESS;
}
