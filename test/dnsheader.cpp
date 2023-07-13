#include <cstddef>
#include <stdio.h>
#include <cstring>

// based on https://www.fauser.edu/~fuligni/files/classi5/sistemi-reti/project1-primer%20(DNS%20message%20structure).pdf

struct dns_header {
    // stack 1
    unsigned short id; // 16 bit & 2 byte length

    // stack 2
    unsigned short qr: 1; // 1 if answer, 0 if query type
    unsigned short opcode: 4; // operation
    unsigned short aa: 1; // authoritive answer
    unsigned short tc: 1; // truncated
    unsigned short rd: 1; // recrusion desired
    unsigned short ra: 1; // Recursion Available
    unsigned short zero: 3; // unused
    unsigned short rcode: 4; // response code

    // stack 3
    unsigned short QDCOUNT;

    // stack 4
    unsigned short ANCOUNT;

    // stack 5
    unsigned short NSCOUNT;

    // stack 6
    unsigned short ARCOUNT;
};
int main()
{
    unsigned char buf[65536];
    printf("strlen before: %lu\n", strlen((const char *)buf));
    unsigned char ret[65536];
    struct dns_header *dns = NULL;

    dns = (struct dns_header*)&buf;
    dns->id = 69;
    
    dns->qr = 0b0;
    dns->opcode = 0b0;
    dns->tc = 0b0;
    dns->rd = 0b1;
    dns->ra = 0b0;
    dns->zero = 0b0;
    dns->rcode = 0b0;

    printf("%s\n", buf);
    printf("strlen after: %lu\n", strlen((const char *)buf));
    struct dns_header *dnsres = NULL;
    dnsres = (struct dns_header*)&buf;

    printf("%d", dnsres->id);
    // file

    FILE *f;
    f = fopen("test1","wb");
    fwrite(&buf,sizeof(buf),1,f);
    fclose(f);



    return 0;
}