#ifndef _HEADER_FILE_UDP_RECV_HPP_
#define _HEADER_FILE_UDP_RECV_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "u2h_msg.hpp"

#define MAXLINE 8192    
    
void u2h_udp_recv(int sockfd, sockaddr_in * pcliaddr, socklen_t clilen)
{
    int     n;
    socklen_t len;
    char    mesg[MAXLINE];

    for ( ; ; ) 
    {
        bzero(mesg, sizeof(mesg));
        len = clilen;
        n = recvfrom(sockfd, mesg, MAXLINE, 0, (sockaddr *)pcliaddr, &len);
        if(-1==n)
        {
            printf("recvfrom return -1,errno=%d,%s \n",errno,strerror(errno));
        }
        else
        {
            char ip[20] ={0};
            inet_ntop(AF_INET,&(pcliaddr->sin_addr.s_addr),ip,sizeof(ip));
            printf("recvfrom %s:%d,%s \n",ip,pcliaddr->sin_port,mesg);            
            U2HMsg msg(mesg);
            msg.Process();
        }
    }
}

#endif // _HEADER_FILE_UDP_RECV_HPP_
