#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stddef.h>    // size_t
#include <stdbool.h>   // bool

#include "types.h"

struct ServerReq {
    char* data;
    size_t size;
    ipaddr_t addr;
    sockfd_t clientfd;
    char* (*readBytes) (ServerReq* req, size_t size);
    char* (*readLine)  (ServerReq* req);
    bool  (*readf)     (ServerReq* req, const char* fmt, ...) __attribute__((format(scanf, 2, 3)));
};

ServerReq* ServerReq_new(sockfd_t clientfd, ipaddr_t addr);
void ServerReq_delete(ServerReq** req);

char* ServerReq_readBytes (ServerReq* req, size_t size);
char* ServerReq_readLine  (ServerReq* req);
bool ServerReq_readf      (ServerReq* req, const char* fmt, ...) __attribute__((format(scanf, 2, 3)));

#endif
