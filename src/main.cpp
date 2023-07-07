#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "parser/parser.h"
#include <cstddef>
#include <cstdio>

int main(int argc, char **argv)
{
    struct parser_target parser_target;
    char *resultbuffer;

    parser_init(&parser_target, argc, argv);
    //parser_get(&parser_target, &resultbuffer, (char*)"kkk");
    printf("parseretq: %d\n", parser_get(&parser_target, &resultbuffer, (char*)"port"));
    printf("str: %s\n", resultbuffer); 
    printf("parseretq: %d\n", parser_get(&parser_target, &resultbuffer, (char*)"addr"));
    printf("str: %s\n", resultbuffer); 
    return 0;
}