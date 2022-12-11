#include <errno.h>     // errno
#include <stdlib.h>    // exit, abort
#include <stdio.h>     // fprintf, stderr

#include "io.h"

void __server_print_err(const char* msg, int err_code)
{
    if (!err_code && errno)
        fprintf(stderr, "libserver: %s: %s\n", msg, strerror(errno));
    else
        fprintf(stderr, "libserver: error: %s\n", msg);
#ifdef DEBUG
    abort();
#else
    exit(err_code ? err_code : errno);
#endif
}
