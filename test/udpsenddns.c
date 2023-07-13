#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>

struct dns_header {
    // stack 1
    unsigned char id; // 16 bit & 2 byte length

    // stack 2
    unsigned short qr: 1; // 1 if answer, 0 if query type
    unsigned short opcode: 5; // operation
    unsigned short aa: 1; // authoritive answer
    unsigned short tc: 1; // truncated
    unsigned short rd: 1; // recrusion desired
    unsigned short ra: 1; // Recursion Available
    unsigned short zero: 3; // unused
    unsigned short rcode: 3; // response code

    // stack 3
    unsigned short QDCOUNT;

    // stack 4
    unsigned short ANCOUNT;

    // stack 5
    unsigned short NSCOUNT;

    // stack 6
    unsigned short ARCOUNT;
    unsigned char qcount;
    unsigned char anscount;
    unsigned char authcount;
    unsigned char addcount;
    unsigned char qname;

};

int main()
{
    int sockfd, ret, recvbytes;
    struct sockaddr_in serverAddress;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        perror("socket");
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(53);

    if ((ret = bind(sockfd, (const struct sockaddr *)&serverAddress, 
            sizeof(serverAddress)))) {
        perror("bind");
        close(sockfd);
    }

    // here
    
    struct sockaddr_in clientAddress;
    
    char buf[1024];
    struct dns_header *dnsres = NULL;
    socklen_t socklen = sizeof (clientAddress);

    for(;;) {
        
        recvbytes = recvfrom(sockfd, &buf, sizeof(buf), 0, 
                (struct sockaddr*)&clientAddress, &socklen);
        dnsres = (struct dns_header*)&buf;

        // std::string s = std::("{:x}", std::byte(42));
        // printf("%d\n", dnsres->id);
        

    }
    return 0;
}