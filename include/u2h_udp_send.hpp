#ifndef _HEADER_FILE_UDP_SEND_HPP_
#define _HEADER_FILE_UDP_SEND_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "u2h_udp_deli.hpp"

#define MAXLINE 8192    

void u2h_SetBlocking(int sockfd,bool blocking)
{
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (-1==flags)
        return;
    int rt =0;
    if ( (flags&O_NONBLOCK) && blocking )
        rt = fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);
    else if ( !(flags&O_NONBLOCK) && false==blocking )
        rt = fcntl(sockfd, F_SETFL, flags|O_NONBLOCK);
    else
        ; // Already set.
}

int u2h_udp_send(const std::string & udpServerIp,int udpServerPort,
    const std::string & url,const std::string & data)
{ 
    int res =0;
    do
    {
        struct sockaddr_in servaddr; 
        socklen_t servlen =sizeof(servaddr);
        bzero(&servaddr, sizeof(servaddr)); 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_port = htons(udpServerPort); 
        if(inet_pton(AF_INET, udpServerIp.c_str(), &servaddr.sin_addr) <= 0) 
        { 
            res =1;
        } 
        static int sockfd = socket(AF_INET, SOCK_DGRAM, 0);   
        u2h_SetBlocking(sockfd,false);

        std::string sbuf =url+DELI;
        sbuf +=data;
        ssize_t n =sendto(sockfd, sbuf.c_str(), sbuf.size()>MAXLINE?MAXLINE:sbuf.size(), 0, 
            (struct sockaddr *)&servaddr, servlen);
        if(n==-1)
        {
            printf("sendto failed! errno=%d,%s \n",errno,strerror(errno));
            res =1;
        }
    }while(0);
    return res; 
}

#endif // _HEADER_FILE_UDP_SEND_HPP_
