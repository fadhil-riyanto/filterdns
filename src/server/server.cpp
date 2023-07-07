#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>

int sock_init(struct sock_instance *sock_instance)
{
    sock_instance->sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
        do_sockfd_cleanup(sock_instance->sockfd);
    }
    return ret;
}

int sock_listen(struct sock_instance *sock_instance)
{
    int ret;
    if ((ret = listen(sock_instance->sockfd, CONN_MAX_CLIENTS))) {
        perror("listen");
        do_sockfd_cleanup(sock_instance->sockfd);
    }
    return ret;
}

void do_sockfd_cleanup(void *sockfd)
{
    free(sockfd);
}