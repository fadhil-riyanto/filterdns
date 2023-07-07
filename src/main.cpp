#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "utils/parser.h"
#include "server/server.h"
#include <cstddef>
#include <cstdio>
#include <stdlib.h>

struct server_properties
{
    int port;
    char *addr;
};

int _main(struct server_properties *server_properties)
{
    fprintf(stdout, "starting program %s:%d", server_properties->addr, server_properties->port);
    return 0;
}

int main(int argc, char **argv)
{
    struct parser_target parser_target;
    struct server_properties server_properties;
    char *resultbuffer;

    parser_init(&parser_target, argc, argv);

    if (parser_get(&parser_target, &resultbuffer, (char*)"port") 
                == PARSE_INCOMPELETE_ARGS) {
        fprintf(stderr, "warn, incompelete args at %s, use --port portnum --addr ipv4addr\n", parser_err_where(&parser_target));
        return -1;
    }
    server_properties.port = atoi(resultbuffer);

    if (parser_get(&parser_target, &resultbuffer, (char*)"addr") 
                == PARSE_INCOMPELETE_ARGS) {
        fprintf(stderr, "warn, incompelete args at %s, use --port portnum --addr ipv4addr\n", parser_err_where(&parser_target));
        return -1;
    }
    server_properties.addr = resultbuffer;
    
    //parser_get(&parser_target, &resultbuffer, (char*)"kkk");
    // printf("parseretq: %d\n", parser_get(&parser_target, &resultbuffer, (char*)"port"));
    // printf("str: %s\n", resultbuffer); 
    // printf("parseretq: %d\n", parser_get(&parser_target, &resultbuffer, (char*)"addr"));
    // printf("str: %s\n", resultbuffer); 
    
    return _main(&server_properties);
}