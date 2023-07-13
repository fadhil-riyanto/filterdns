#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <cstddef>
#endif

#include "server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "../utils/debugger.h"

struct dns_header {
    // stack 1
    unsigned short id; // 16 bit & 2 byte length

    // stack 2
    unsigned char qr :1; // query/response flag
    unsigned char opcode :4; // purpose of message
    unsigned char aa :1; // authoritive answer
    unsigned char tc :1; // truncated message
    unsigned char rd :1; // recursion desired
    unsigned char ra :1; // recursion available
    unsigned char z :1; // its z! reserved
    unsigned char rcode :4; // response code


    // // stack 2
    // unsigned char rd :1; // recursion desired
    // unsigned char tc :1; // truncated message
    // unsigned char aa :1; // authoritive answer
    // unsigned char opcode :4; // purpose of message
    // unsigned char qr :1; // query/response flag
 
    // unsigned char rcode :4; // response code
    // unsigned char cd :1; // checking disabled
    // unsigned char ad :1; // authenticated data
    // unsigned char z :1; // its z! reserved
    // unsigned char ra :1; // recursion available

    // stack 3
    unsigned short QDCOUNT;

    // stack 4
    unsigned short ANCOUNT;

    // stack 5
    unsigned short NSCOUNT;

    // stack 6
    unsigned short ARCOUNT;
    unsigned char name[];
};

int sock_init(struct sock_instance *sock_instance)
{
    sock_instance->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_instance->sockfd == -1)
        perror("socket");
    
    return sock_instance->sockfd;
}

int sock_bind(struct sock_instance *sock_instance, int port, char *addr)
{
    int ret;

    sock_instance->serverAddress.sin_family = AF_INET;
    sock_instance->serverAddress.sin_addr.s_addr = INADDR_ANY;
    sock_instance->serverAddress.sin_port = htons(port);

    if ((ret = bind(sock_instance->sockfd, (const struct sockaddr *)&sock_instance->serverAddress, 
            sizeof(sock_instance->serverAddress)))) {
        perror("bind");
        do_cleanup(sock_instance->sockfd);
    }

    return ret;
}

int sock_listen(struct sock_instance *sock_instance)
{
    int ret, clientfd, recvbytes;
    struct sockaddr_in clientAddress;
    char buf[65536];
    // unsigned char *bufs;
    struct dns_header *dnsres = NULL;

    socklen_t socklen = sizeof (clientAddress);

    for(;;) {
        
        recvbytes = recvfrom(sock_instance->sockfd, &buf, 65536, 0, 
                (struct sockaddr*)&clientAddress, &socklen);
        // buf[recvbytes] = '\0';
        //hexDump("stringku", &bufs, sizeof(bufs), 16);

        // std::string s = std::("{:x}", std::byte(42));
        dnsres = (struct dns_header*)&buf;
        printf("dataa: %s\n", dnsres->name);


        //debugArray((const unsigned char *)buf, sizeof(buf));
        // for (int ii = 1; ii < recvbytes; ii++) {
        //     printf("data: %x", buf[ii]);
        // }
        // memset(buf, 0, DNS_BUF);
        // char aaaa[8] = "fadhil\0";
        
        // sendto(sock_instance->sockfd, &aaaa, sizeof(aaaa), 0, (struct sockaddr*)&clientAddress, socklen);
    }
// 123456789


    // if ((ret = listen(sock_instance->sockfd, CONN_MAX_CLIENTS))) {
    //     perror("listen");
    //     do_cleanup(sock_instance->sockfd);
    // }
    // while (1)
    // {
    //     socklen_t clientAddressLength = sizeof(clientAddress);
    //     clientfd = accept(sock_instance->sockfd, (struct sockaddr*)&clientAddress, &clientAddressLength);

    //     char aaaa[8] = "fadhil\0";
    //     sendto(clientfd, aaaa, sizeof(aaaa), 0, (struct sockaddr*)&clientAddress, sizeof(clientAddress));
    // }
    return ret;
}

int do_cleanup(int sockfd)
{
    return close(sockfd);
}

int epoll_init(struct sock_instance *sock_instance)
{
    int ret;
    if ((ret = epoll_create(0)) == -1) {
        perror("epoll");
        close(ret);
        return -1;
    }
    sock_instance->epollfd = ret;
    return ret;
}

int epoll_setprop(struct sock_instance *sock_instance, EPOLL_EVENTS event_type,
         int operation)
{
    int ret;

    sock_instance->event.events = event_type;
    sock_instance->event.data.fd = sock_instance->sockfd;
    if ((ret = epoll_ctl(sock_instance->epollfd, operation, 
            sock_instance->sockfd, sock_instance->events)) == -1) {
        perror("epoll_ctl");
        do_cleanup(sock_instance->sockfd);
        do_cleanup(sock_instance->epollfd);
    }
    return 0;
}