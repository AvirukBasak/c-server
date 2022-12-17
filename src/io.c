#include <errno.h>     // errno
#include <stdlib.h>    // exit, abort, free
#include <stdio.h>     // fprintf, stderr

#include "io.h"
#include "request.h"
#include "stdfunc.h"

void server_print_err(const char* msg, int err_code)
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

void server_print_connlog(ServerReq* req)
{
    // log request reciept
    const char* datetime = NULL;
    printf("[%s] - %d.%d.%d.%d accepted\n",
        datetime = server_std_gettime(),
        req->addr[0], req->addr[1], req->addr[2], req->addr[3],
    );
    free((void*) datetime);
}

void server_print_connclose(ServerReq* req)
{
    // connection closed by client
    const char* datetime = NULL;
    printf("[%s] - %d.%d.%d.%d client closed connection\n",
        datetime = server_std_gettime(),
        req->addr[0], req->addr[1], req->addr[2], req->addr[3]
    );
    free((void*) datetime);
}
