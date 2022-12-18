#ifndef __SIGHANDLERS_H__
#define __SIGHANDLERS_H__

#include <unistd.h>    // SIG*, sig_atomic_t

extern volatile sig_atomic_t sigint_stop;

void server_sigint_handler(int signum);
void server_sigpipe_handler(int signum);

#endif
