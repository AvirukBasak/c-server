#include "stdhead.h"
#include "io.h"
#include "socket.h"
#include "server.h"
#include "request.h"
#include "response.h"

Server* Server_new()
{
    Server* sv = malloc(sizeof(Server));
    __server_t* priv = malloc(sizeof(__server_t));
    if (!sv) __server_print_err("null pointer");
    if (!priv) __server_print_err("null pointer");
    sv->priv = priv;
    sv->set_listener = Server_set_listener;
    sv->set_ipaddr = Server_set_ipaddr;
    sv->set_port = Server_set_port;
    sv->delete = Server_delete;
    sv->listen = Server_listen;
    // init server
    sv->set_ipaddr(sv, 127, 0, 0, 1);
    sv->set_port(sv, 8080);
    return sv;
}

void Server_set_listener(Server* sv, void (*listener)(ServerReq*, ServerRes*))
{
    if (!sv) __server_print_err("null pointer");
    if (!listener) __server_print_err("null listener callback function");
    sv->priv->listener = listener;
}

void Server_set_ipaddr(Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3)
{
    if (!sv) __server_print_err("null pointer");
    sv->priv->addr[0] = a0;
    sv->priv->addr[1] = a1;
    sv->priv->addr[2] = a2;
    sv->priv->addr[3] = a3;
}

void Server_set_port(Server* sv, port_t port)
{
    if (!sv) __server_print_err("null pointer");
    sv->priv->port = port;
}

void Server_listen(Server* sv, void (*callback)(ipaddr_t, port_t))
{
    if (!sv) __server_print_err("null pointer");
    if (callback) callback(sv->priv->addr, sv->priv->port);
}

void Server_delete(Server** sv)
{
    if (!sv && !*sv) return;
    free((*sv)->priv);
    free(*sv);
    *sv = NULL;
}
