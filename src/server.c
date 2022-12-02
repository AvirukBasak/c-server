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
    sv->start = Server_start;
    sv->listenWith = Server_listenWith;
    sv->listenAt = Server_listenAt;
    sv->delete = Server_delete;
    return sv;
}

void Server_start(Server* sv, void (*callback)(ipaddr_t a, port_t p))
{
    if (!sv) __server_print_err("null pointer");
    callback(sv->addr, sv->port);
}

void Server_listenWith(Server* sv, void (*callback)(ServerReq*, ServerRes*))
{
    if (!sv) __server_print_err("null pointer");
    sv->listener = callback;
}

void Server_listenAt(Server* sv, ipaddr_t a, port_t p)
{
    if (!sv) __server_print_err("null pointer");
    memcpy(sv->addr, a, 4*sizeof(a[0]));
    sv->port = p;
}

void Server_delete(Server** sv)
{
    if (!sv && !*sv) return;
    free(*sv);
    *sv = NULL;
}
