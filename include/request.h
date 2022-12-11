#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stddef.h>    // size_t

typedef struct ServerReq ServerReq;

struct ServerReq {
    char* data;
    size_t size;
    void (*delete)(ServerReq** res);
};

ServerReq* ServerReq_new();
void ServerReq_delete(ServerReq** req);

#endif
