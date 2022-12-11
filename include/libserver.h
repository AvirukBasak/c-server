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
    void (*set_listener) (Server* sv, void (*listener)(ServerReq*, ServerRes*));
    void (*set_ipaddr)   (Server* sv, uint8_t a3, uint8_t a2, uint8_t a1, uint8_t a0);
    void (*set_port)     (Server* sv, port_t port);
    void (*delete)       (Server** sv);
    void (*listen)       (Server* sv, void (*callback)(ipaddr_t, port_t));
    ipaddr_t __addr;
    port_t   __port;
    void (*__listener)(ServerReq*, ServerRes*);
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
