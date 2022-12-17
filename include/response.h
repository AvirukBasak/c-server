#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <stddef.h>   // size_t
#include <inttypes.h> // uint64_t, int64_t
#include <stdbool.h>  // bool

#include "socket.h"

struct ServerRes {
    sockfd_t clientfd;
    bool (*writeBytes) (ServerRes* res, const char* data, size_t size);
    bool (*writef)     (ServerRes* res, const char* fmt, ...) __attribute__((format(printf, 2, 3)));
    void (*end)        (ServerRes* res);
};

ServerRes* ServerRes_new(sockfd_t clientfd);
void ServerRes_delete(ServerRes** res);

bool ServerRes_writeBytes (ServerRes* res, const char* data, size_t size);
bool ServerRes_writef     (ServerRes* res, const char* fmt, ...) __attribute__((format(printf, 2, 3)));
void ServerRes_end        (ServerRes* res);

#endif
