#include <unistd.h>    // SIG*
#include <stdio.h>     // printf, fprintf
#include <stdlib.h>    // exit
#include <stdbool.h>   // bool

#include "sighandlers.h"

volatile sig_atomic_t sigint_stop;

void server_sigint_handler(int signum)
{
    if (signum != SIGINT) return;
    printf("\r\n");
    sigint_stop = true;
    exit(0);
}

void server_sigpipe_handler(int signum)
{
    if (signum != SIGPIPE) return;
#if 0 // #ifdef DEBUG
    fprintf(stderr, "libserver: recieved SIGPIPE\n");
#else
    signal(SIGPIPE, SIG_IGN);
    return;
#endif
}
