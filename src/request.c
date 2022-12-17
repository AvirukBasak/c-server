#include <stdlib.h>      // malloc, realloc
#include <stdbool.h>     // bool
#include <stdarg.h>      // va_*

#include "types.h"
#include "errcodes.h"
#include "io.h"
#include "server.h"
#include "socket.h"
#include "request.h"

ServerReq* ServerReq_new(
    char *data,         // request data
    size_t size,        // request data size
    sockfd_t clientfd,  // clientfd, response destination
    ipaddr_t addr       // client ip address
) {
    ServerReq* req = malloc(sizeof(ServerReq));
    if (!req) server_print_err("null pointer", E_NULLPTR);
    req->data = data;
    req->size = size;
    server_socket_try(clientfd, "client socket fd invalid");
    req->clientfd = clientfd;
    req->addr[0] = addr[0];
    req->addr[1] = addr[1];
    req->addr[2] = addr[2];
    req->addr[3] = addr[3];
    req->readBytes = ServerReq_readBytes;
    req->readLine = ServerReq_readLine;
    req->readf = ServerReq_readf;
    return req;
}

char* ServerReq_readBytes(ServerReq* req, size_t size)
{
    if (req->data) free(req->data);
    req->size = size;
    req->data = malloc(size +1);
    recv(req->clientfd, req->data, req->size, 0);
    req->data[size] = 0;
    return req->data;
}

char* ServerReq_readLine(ServerReq* req)
{
    if (req->data) free(req->data);
    req->size = 0;
    req->data = malloc(1);
    if (!req->data) server_print_err("null pointer", E_NULLPTR);
    char c0, c1 = 0;
    while (true) {
        c0 = c1;
        recv(req->clientfd, &c1, 1, 0);
        if (c1 == '\n' || (signed char) c1 == EOF) {
            if (c0 == '\r') req->data[--req->size] = 0;
            else req->data[req->size] = 0;
            return req->data;
        }
        req->data[req->size] = c1;
        req->data = realloc(req->data, ++req->size +1);
    }
    return NULL;
}

void ServerReq_readf(ServerReq* req, const char* fmt, ...)
{
    va_list args;                      // args
    va_start(args, fmt);               // init args
    char* line = req->readLine(req);
    vsscanf(line, fmt, args);
    va_end(args);                      // end args
    free(line);                        // free buffer
}

void ServerReq_delete(ServerReq** req)
{
    if (!req && !*req) return;
    if ((*req)->data) free((*req)->data);
    free(*req);
    *req = NULL;
}
