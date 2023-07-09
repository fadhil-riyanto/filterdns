#include <stdio.h>
#include <string.h>

int main()
{
     FILE *fptr;
    fptr = fopen("sample.example.com", "rb");
    char buf[65536];

    //fgets(buf, 65536, fptr);
    printf("%zu\n", sizeof(buf));

}