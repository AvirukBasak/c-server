#include <unistd.h>    // SIG*
#include <stdio.h>     // printf, fprintf
#include <stdlib.h>    // exit

#include "sighandlers.h"

void __server_sigint_handler(int signum)
{
    if (signum != SIGINT) return;
    printf("\r\n");
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
