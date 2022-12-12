#ifndef __SIGHANDLERS_H__
#define __SIGHANDLERS_H__

#include <unistd.h>    // signal, SIG*, sig_atomic_t

extern volatile sig_atomic_t __sigint_stop;

void __server_sigint_handler(int signum);
void __server_sigpipe_handler(int signum);

#endif
