#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stddef.h>    // size_t

#include "types.h"
#include "server.h"
#include "socket.h"

struct ServerReq {
    char* data;
    size_t size;
    ipaddr_t addr;
    sockfd_t clientfd;
    char* (*readBytes) (ServerReq* req, size_t size);
    char* (*readLine)  (ServerReq* req);
};

ServerReq* ServerReq_new(char *data, size_t size, sockfd_t clientfd, ipaddr_t addr);
void ServerReq_delete(ServerReq** req);

char* ServerReq_readBytes (ServerReq* req, size_t size);
char* ServerReq_readLine  (ServerReq* req);

#endif
