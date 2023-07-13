#ifndef _DEBUGGER_H
#define _DEBUGGER_H

void hexDump (
    const char * desc,
    const void * addr,
    const int len,
    int perLine
);

#endif