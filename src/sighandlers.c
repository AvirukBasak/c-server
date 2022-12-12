#include <unistd.h>    // SIG*
#include <stdio.h>     // printf, fprintf
#include <stdlib.h>    // exit
#include <stdbool.h>   // bool

#include "sighandlers.h"

volatile sig_atomic_t __sigint_stop;

void __server_sigint_handler(int signum)
{
    if (signum != SIGINT) return;
    printf("\r\n");
    __sigint_stop = true;
    exit(0);
}

void __server_sigpipe_handler(int signum)
{
    if (signum != SIGPIPE) return;
#ifdef DEBUG
    fprintf(stderr, "Received SIGPIPE\n");
#else
    signal(SIGPIPE, SIG_IGN);
    return;
#endif
}
