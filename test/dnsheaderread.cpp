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
    FILE *f;
    
    f = fopen("test1","rb");
    struct dns_header *dnsres = NULL;
    fread(&buf,sizeof(buf),1,f);

    dnsres = (struct dns_header*)&buf;

    printf("%d", dnsres->id);
    fclose(f);



    return 0;
}