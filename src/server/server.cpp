#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <sys/epoll.h>
#endif

#include "server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

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
    char buf[DNS_BUF];

    socklen_t socklen = sizeof (clientAddress);

    for(;;) {
        //buf = NULL;
        
        recvbytes = recvfrom(sock_instance->sockfd, &buf, sizeof(buf), 0, 
                (struct sockaddr*)&clientAddress, &socklen);
        buf[recvbytes] = '\0';
        printf("%s", buf);
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