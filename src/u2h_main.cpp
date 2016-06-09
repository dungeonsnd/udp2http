

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "u2h_udp_recv.hpp"
#include "u2h_msg.hpp"


#define ERR(msg) \
    { \
        printf("%s errno=%d,%s \n",msg,errno,strerror(errno)); \
        exit(0); \
    }
    

int main(int argc, char * argv[])
{
    if(argc<2)
    {
        printf("Usage: %s <port> \n",argv[0]);
        return 1;
    }
    int port =atoi(argv[1]);

    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1==sockfd)
        ERR("socket failed! ")
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    
    bind(sockfd, (sockaddr *) &servaddr, sizeof(servaddr));
    if (-1==sockfd)
        ERR("bind failed! ")
        
    u2h_udp_recv(sockfd, &cliaddr, sizeof(cliaddr));

    return 0;
}
