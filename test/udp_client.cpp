

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "u2h_udp_send.hpp"



int main(int argc, char * argv[])
{
    for(int i=0;i<100000;i++)
    {
        int rt =u2h_udp_send("127.0.0.1",17070,"www.test.com","k=v");
        printf("i=%d, rt=%d \n",i,rt);
    }
    return 0;
}
