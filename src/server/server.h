#ifndef _SERVER_H
#define _SERVER_H

#define EPOLL_MAX_EVENTS 100
#define CONN_MAX_CLIENTS 50

#include <netinet/in.h>
#include <sys/epoll.h>

struct sock_instance
{
    int sockfd;
    int epollfd;

    struct sockaddr_in serverAddress;
    struct epoll_event event, events[EPOLL_MAX_EVENTS];
};

static const int DNS_BUF = 1024;

int sock_init(struct sock_instance *sock_instance);
int sock_bind(struct sock_instance *sock_instance, int port, char *addr);
int sock_listen(struct sock_instance *sock_instance);
int do_cleanup(int sockfd);

int epoll_init(struct sock_instance *sock_instance);
int epoll_setprop(struct sock_instance *sock_instance, EPOLL_EVENTS event_type, int operation);

#endif