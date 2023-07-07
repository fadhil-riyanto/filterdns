#ifndef _PARSER_H
#define _PARSER_H

#define PARSE_INCOMPELETE_ARGS 30
#define PARSE_MISMATCH_ARGS 31

struct parser_target {
    int argc;
    char **argv;
};

void parser_init(struct parser_target *parser_target, int argc, char **argv);
int parser_get(struct parser_target *parser_target, char **buf, char *prop);

#endif