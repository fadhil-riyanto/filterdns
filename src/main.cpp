#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "parser/parser.h"
#include "server/server.h"
#include <cstddef>
#include <cstdio>

void __main(struct parser_target *parser_target, int argc, char **argv)
{
    
}

int main(int argc, char **argv)
{
    struct parser_target parser_target;
    char *resultbuffer;

    parser_init(&parser_target, argc, argv);

    if (parser_get(&parser_target, &resultbuffer, (char*)"port") 
                == PARSE_INCOMPELETE_ARGS) {
        fprintf(stderr, "warn, incompelete args at %s, use --port portnum --addr ipv4addr\n", parser_err_where(&parser_target));
        return -1;
    }
    if (parser_get(&parser_target, &resultbuffer, (char*)"addr") 
                == PARSE_INCOMPELETE_ARGS) {
        fprintf(stderr, "warn, incompelete args at %s, use --port portnum --addr ipv4addr\n", parser_err_where(&parser_target));
        return -1;
    }
    
    //parser_get(&parser_target, &resultbuffer, (char*)"kkk");
    // printf("parseretq: %d\n", parser_get(&parser_target, &resultbuffer, (char*)"port"));
    // printf("str: %s\n", resultbuffer); 
    // printf("parseretq: %d\n", parser_get(&parser_target, &resultbuffer, (char*)"addr"));
    // printf("str: %s\n", resultbuffer); 
    
    return 0;
}