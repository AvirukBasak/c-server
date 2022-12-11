#ifndef __SERVER_H__
#define __SERVER_H__

#include "stdhead.h"
#include "request.h"
#include "response.h"

typedef uint8_t ipaddr_t[4];
typedef uint16_t port_t;

typedef struct Server Server;
typedef struct __server_t __server_t;

struct Server {
    void (*set_listener) (Server* sv, void (*listener)(ServerReq*, ServerRes*));
    void (*set_ipaddr)   (Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
    void (*set_port)     (Server* sv, port_t port);
    void (*listen)       (Server* sv, void (*callback)(ipaddr_t, port_t));
    void (*delete)       (Server** sv);
    __server_t* priv;
};

struct __server_t {
    ipaddr_t addr;
    port_t   port;
    void (*listener)(ServerReq*, ServerRes*);
};

Server* Server_new();

void Server_set_listener  (Server* sv, void (*listener)(ServerReq*, ServerRes*));
void Server_set_ipaddr    (Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
void Server_set_port      (Server* sv, port_t port);
void Server_delete        (Server** sv);
void Server_listen        (Server* sv, void (*callback)(ipaddr_t, port_t));

#endif
