#include <stdio.h>
#include <string.h>

// ref -> https://www.rfc-editor.org/rfc/rfc1035

void ChangetoDnsNameFormat(char* dns,char* host) 
{
    int lock = 0 , i;
    strcat(host,".");
     
    for(i = 0 ; i < strlen((char*)host) ; i++) 
    {
        if(host[i]=='.') 
        {
            *dns++ = i-lock;
            for(;lock<i;lock++) 
            {
                *dns++=host[lock];
            }
            lock++; //or lock=i+1;
        }
    }
    *dns++='\0';
}

int main() {
    char t[200], *qname;

    char host[15] = "www.google.com\0";
    ChangetoDnsNameFormat((char*)&t, host);

    printf("%s", t);
    // char *host = "google.com";
    // ChangetoDnsNameFormat(qname, host);
    // printf("%s\n", t);
    return 2;
}