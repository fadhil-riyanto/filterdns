#include <stdio.h>
#include <limits.h>

struct aaaa {
    unsigned char a: 1;
    unsigned char b: 2;
    unsigned char c: 3;
};
int main()
{
    struct aaaa aaaa;
    aaaa.a = 0b000000; // 0
    aaaa.b = 0b000010; // 2
    aaaa.c = 0b000100; // 4
    
    
    printf("%d %d %d\n", aaaa.a, aaaa.b, aaaa.c);
    printf("%lu", (CHAR_BIT * sizeof(aaaa)));
}