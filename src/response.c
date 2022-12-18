#include <stdlib.h>      // malloc
#include <stdarg.h>      // va_*
#include <unistd.h>      // close
#include <sys/socket.h>  // send

#include "response.h"
#include "errcodes.h"
#include "io.h"
#include "socket.h"

ServerRes* ServerRes_new(sockfd_t clientfd)
{
    if (!server_socket_isvalid(clientfd)) return NULL;
    ServerRes* res = malloc(sizeof(ServerRes));
    if (!res) server_print_err("null pointer", E_NULLPTR);
    res->clientfd = clientfd;
    res->writeBytes = ServerRes_writeBytes;
    res->writef = ServerRes_writef;
    res->end = ServerRes_end;
    return res;
}

void ServerRes_delete(ServerRes** res)
{
    if (!res && !*res) return;
    if (server_socket_isvalid((*res)->clientfd))
        close((*res)->clientfd);
    free(*res);
    *res = NULL;
}

bool ServerRes_writeBytes(ServerRes* res, const char* data, size_t size)
{
    if (!res->clientfd) return false;
    if (server_socket_isvalid(res->clientfd))
        send(res->clientfd, data, size, 0);
    return true;
}

bool ServerRes_writef(ServerRes* res, const char* fmt, ...)
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/va-arg-va-copy-va-end-va-start?view=msvc-170#example
{
    if (!res->clientfd) return false;
    va_list args;                                 // original args
    va_list args_copy;                            // copy of args for 2nd pass
    va_start(args, fmt);                          // init original args
    va_copy(args_copy, args);                     // make args copy
    size_t size = vsnprintf(NULL, 0, fmt, args);  // compute required bytes
    va_end(args);                                 // end original args
    char* buffer = malloc(size +2);               // allocate required bytes
    vsnprintf(buffer, size +1, fmt, args_copy);   // write to buffer from copy
    va_end(args_copy);                            // end copy
    if (server_socket_isvalid(res->clientfd))
        send(res->clientfd, buffer, size, 0);     // send off data
    free(buffer);                                 // free buffer
    return true;
}

void ServerRes_end(ServerRes* res)
{
    if (!res->clientfd) return;
    if (server_socket_isvalid(res->clientfd))
        close(res->clientfd);
    res->clientfd = 0;
}
