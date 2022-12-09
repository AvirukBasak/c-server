#ifndef __SERVER_H__
#define __SERVER_H__

#include "stdhead.h"
#include "request.h"
#include "response.h"

typedef uint8_t ip4addr_t[4];
typedef uint16_t ip6addr_t[8];
typedef uint16_t port_t;

typedef struct Server Server;

struct Server {
    void (*listen)     (Server* sv, void (*callback) (Server* sv));
    void (*listener)   (ServerReq* req, ServerRes* res);
    void (*delete)     (Server** sv);
    ip4addr_t ip4_addr;
    ip6addr_t ip6_addr;
    port_t   port;
};

Server* Server_new();

void Server_listen        (Server* sv, void (*callback) (Server* sv));
void Server_delete        (Server** sv);

#endif
