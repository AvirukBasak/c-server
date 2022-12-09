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
    sv->listen = Server_listen;
    sv->delete = Server_delete;
    sv->ip4_addr = { 127, 0, 0, 1 };
    sv->ip6_addr = NULL;
    sv->port = 8080;
    return sv;
}

void Server_listen(Server* sv, void (*callback)(const Server* sv))
{
    if (!sv) __server_print_err("null pointer");
    if (!sv->ip4_addr && !sv->ip6_addr) sv->ip4_addr = { 127, 0, 0, 1 };
    if (!sv->port) sv->port = 8080;
    if (callback) callback(sv);
}

void Server_delete(Server** sv)
{
    if (!sv && !*sv) return;
    free(*sv);
    *sv = NULL;
}
