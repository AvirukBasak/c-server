#ifndef __LIBSERVER_H__
#define __LIBSERVER_H__

#include <stddef.h>
#include <inttypes.h>

typedef uint8_t ip4addr_t[4];
typedef uint16_t ip6addr_t[8];
typedef uint16_t port_t;

typedef struct Server Server;
typedef struct ServerReq ServerReq;
typedef struct ServerRes ServerRes;

struct Server {
    void (*listen)     (Server* sv, void (*callback) (Server* sv));
    void (*listener)   (ServerReq* req, ServerRes* res);
    void (*delete)     (Server** sv);
    ip4addr_t ip4_addr;
    ip6addr_t ip6_addr;
    port_t   port;
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
