#include "stdhead.h"
#include "io.h"
#include "socket.h"
#include "server.h"
#include "request.h"
#include "response.h"

Server* Server_new()
{
    Server* sv = malloc(sizeof(Server));
    if (!sv) __server_print_err("null pointer");
    sv->set_listener = Server_set_listener;
    sv->set_ipaddr Server_set_ipaddr;
    sv->set_port = Server_set_port;
    sv->delete = Server_delete;
    sv->listen = Server_listen;
    // init server
    return sv;
}

void Server_set_listener(Server* sv, void (*listener)(ServerReq*, ServerRes*)
{
    if (!sv) __server_print_err("null pointer");
    if (!listener) __server_print_err("null listener callback function");
    sv->listener = listener;
}

void Server_set_ipaddr(Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3)
{
    if (!sv) __server_print_err("null pointer");
    sv->addr[0] = a0;
    sv->addr[1] = a1;
    sv->addr[2] = a2;
    sv->addr[3] = a3;
}

void Server_set_port(Server* sv, port_t port)
{
    if (!sv) __server_print_err("null pointer");
    sv->port = port;
}

void Server_listen(Server* sv, void (*callback)(ipaddr_t, port_t))
{
    if (!sv) __server_print_err("null pointer");
    if (callback) callback(sv);
}

void Server_delete(Server** sv)
{
    if (!sv && !*sv) return;
    free(*sv);
    *sv = NULL;
}
