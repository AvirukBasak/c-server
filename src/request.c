#include <stdlib.h>      // malloc, realloc, free
#include <stdarg.h>      // va_*
#include <sys/socket.h>  // recv, send

#include "request.h"
#include "errcodes.h"
#include "io.h"
#include "socket.h"

ServerReq* ServerReq_new(
    sockfd_t clientfd,  // clientfd, response destination
    ipaddr_t addr       // client ip address
) {
    if (!server_socket_isvalid(clientfd)) return NULL;
    ServerReq* req = malloc(sizeof(ServerReq));
    if (!req) server_print_err("null pointer", E_NULLPTR);
    req->data = NULL;
    req->size = 0;
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
    if (!req->clientfd) return NULL;
    if (req->data) free(req->data);
    req->data = malloc(size +1);
    size_t sz = req->size = recv(req->clientfd, req->data, size, 0);
    while (sz && req->size < size) {
        sz = recv(req->clientfd, req->data + req->size, size - req->size, 0);
        req->size += sz;
    }
    if (!sz) {
        server_print_connclose(req);
        req->clientfd = 0;
    }
    req->data[req->size] = 0;
    return req->data;
}

char* ServerReq_readLine(ServerReq* req)
{
    if (!req->clientfd) return NULL;
    if (req->data) free(req->data);
    req->size = 0;
    req->data = malloc(1);
    if (!req->data) server_print_err("null pointer", E_NULLPTR);
    char c0, c1 = 0;
    while (true) {
        c0 = c1;
        size_t sz = recv(req->clientfd, &c1, 1, 0);
        if (!sz) {
            server_print_connclose(req);
            req->clientfd = 0;
            req->data[req->size] = 0;
            return req->data;
        }
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

bool ServerReq_readf(ServerReq* req, const char* fmt, ...)
{
    if (!req->clientfd) return false;
    va_list args;                      // args
    va_start(args, fmt);               // init args
    char* line = req->readLine(req);
    vsscanf(line, fmt, args);
    va_end(args);                      // end args
    return true;
}

void ServerReq_delete(ServerReq** req)
{
    if (!req && !*req) return;
    if ((*req)->data) free((*req)->data);
    free(*req);
    *req = NULL;
}
