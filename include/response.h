#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <stddef.h>   // size_t
#include <inttypes.h> // uint64_t, int64_t

#include "socket.h"

struct ServerRes {
    sockfd_t clientfd;
    void (*writeBytes) (ServerRes* res, const char* data, size_t size);
    void (*writeStr)   (ServerRes* res, const char* str);
    void (*writeU64)   (ServerRes* res, uint64_t n);
    void (*writeI64)   (ServerRes* res, int64_t n);
    void (*writeHex)   (ServerRes* res, uint64_t n);
    void (*end)        (ServerRes* res);
    void (*delete)     (ServerRes** res);
};

ServerRes* ServerRes_new(sockfd_t clientfd);
void ServerRes_delete(ServerRes** res);

void ServerRes_writeBytes (ServerRes* res, const char* data, size_t size);;
void ServerRes_writeStr   (ServerRes* res, const char* str);
void ServerRes_writeU64   (ServerRes* res, uint64_t n);
void ServerRes_writeI64   (ServerRes* res, int64_t n);
void ServerRes_writeHex   (ServerRes* res, uint64_t n);
void ServerRes_end        (ServerRes* res);

#endif
