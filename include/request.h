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
    void (*delete)(ServerReq** res);
};

ServerReq* ServerReq_new(char *data, size_t size, sockfd_t clientfd, ipaddr_t addr);
void ServerReq_delete(ServerReq** req);

#endif
