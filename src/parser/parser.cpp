#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <cstddef>
#endif

#include <cstdio>
#include <cstring>
#include "parser.h"

void parser_init(struct parser_target *parser_target, int argc, char **argv)
{
    parser_target->argc = argc;
    parser_target->argv = argv;
}

int parser_get(struct parser_target *parser_target, char **buf, char *prop)
{
    *buf = NULL;
    char *tempval;

    for(int x = 0; x < parser_target->argc; x++) {
        //printf("lit %d\n", x);
        
        if (x % 2 != 0) {
            if ('-' == parser_target->argv[x][0] && '-' == parser_target->argv[x][1])
                tempval = &parser_target->argv[x][2];
            else if ('-' == parser_target->argv[x][0])
                tempval = &parser_target->argv[x][1];
            
            //printf("%d\n", strcmp(tempval, prop) );
            if (strcmp(tempval, prop) == 0) {
                if ((x + 1) <= (parser_target->argc - 1)) {
                    //printf("%s", parser_target->argv[x + 1]);
                    *buf = parser_target->argv[x + 1];
                    return 0;
                } else {
                    *buf = NULL;
                    //printf("%s", "kosong");
                    return PARSE_INCOMPELETE_ARGS;
                }
                // printf("%s", "heal");
                //printf("%d", parser_target->argc);
            }
        }
        
    }
    *buf = NULL;
    return PARSE_INCOMPELETE_ARGS;
}