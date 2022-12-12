#ifndef __SERVER_H__
#define __SERVER_H__

#include <stddef.h>        // size_t
#include <inttypes.h>      // uint8_t, uint16_t, uint64_t, int64_t

#include "types.h"
#include "request.h"
#include "response.h"

typedef struct __server_t __server_t;

struct Server {
    void (*set_handler)  (Server* sv, void (*handler)(ServerReq*, ServerRes*));
    void (*set_ipaddr)   (Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
    void (*set_port)     (Server* sv, port_t port);
    void (*listen)       (Server* sv, void (*callback)(ipaddr_t, port_t));
    void (*delete)       (Server** sv);
    __server_t* priv;
};

struct __server_t {
    ipaddr_t addr;
    port_t   port;
    void (*handler)(ServerReq*, ServerRes*);
};

void __server_init();

Server* Server_new();

void Server_set_handler   (Server* sv, void (*handler)(ServerReq*, ServerRes*));
void Server_set_ipaddr    (Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
void Server_set_port      (Server* sv, port_t port);
void Server_listen        (Server* sv, void (*callback)(ipaddr_t, port_t));
void Server_delete        (Server** sv);

#endif
