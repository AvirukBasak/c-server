#ifndef __SERVER_H__
#define __SERVER_H__

#include "stdhead.h"
#include "request.h"
#include "response.h"

typedef uint8_t ipaddr_t[4];
typedef uint16_t port_t;

typedef struct Server Server;

struct Server {
    void (*start)      (Server* sv, void (*callback) (ipaddr_t a, port_t p));
    void (*listenWith) (Server* sv, void (*callback) (ServerReq* req, ServerRes* res));
    void (*listenAt)   (Server* sv, ipaddr_t a, port_t p);
    void (*delete)     (Server** sv);
    ipaddr_t addr;
    port_t   port;
    void (*listener) (ServerReq* req, ServerRes* res);
};

Server* Server_new();

void Server_start         (Server* sv, void (*callback)(ipaddr_t a, port_t p));
void Server_listenWith    (Server* sv, void (*callback)(ServerReq* req, ServerRes* res));
void Server_listenAt      (Server* sv, ipaddr_t a, port_t p);
void Server_delete        (Server** sv);

#endif
