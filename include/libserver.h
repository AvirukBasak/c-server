#ifndef __LIBSERVER_H__
#define __LIBSERVER_H__

#include <stddef.h>
#include <inttypes.h>

typedef uint8_t ipaddr_t[4];
typedef uint16_t port_t;

typedef struct Server Server;
typedef struct ServerReq ServerReq;
typedef struct ServerRes ServerRes;

struct Server {
    void (*start)      (Server* sv, void (*callback) (ipaddr_t a, port_t p));
    void (*listenWith) (Server* sv, void (*callback) (ServerReq* req, ServerRes* res));
    void (*listenAt)   (Server* sv, ipaddr_t a, port_t p);
    void (*delete)     (Server** sv);
};

struct ServerReq {
    char* data;
    size_t size;
};

struct ServerRes {
    void (*writeBytes) (ServerRes* res, const char* data, size_t size);
    void (*writeStr)   (ServerRes* res, const char* str);
    void (*writeU64)   (ServerRes* res, uint64_t n);
    void (*writeI64)   (ServerRes* res, int64_t n);
    void (*writeHex)   (ServerRes* res, void* p);
    void (*send)       (ServerRes* res);
};

Server* Server_new();

#endif
