#include <stdlib.h>    // malloc, free
#include <stdbool.h>   // bool

#include "types.h"
#include "errcodes.h"
#include "io.h"
#include "socket.h"
#include "server.h"
#include "request.h"
#include "response.h"
#include "stdfunc.h"
#include "sighandlers.h"

void server_init()
{
    signal(SIGINT, server_sigint_handler);
    signal(SIGPIPE, server_sigpipe_handler);
}

Server* Server_new()
{
    server_init();
    Server* sv = malloc(sizeof(Server));
    server_privdata_t* priv = malloc(sizeof(server_privdata_t));
    if (!sv) server_print_err("null pointer", E_NULLPTR);
    if (!priv) server_print_err("null pointer", E_NULLPTR);
    sv->priv = priv;
    sv->set_handler = Server_set_handler;
    sv->set_ipaddr = Server_set_ipaddr;
    sv->set_port = Server_set_port;
    sv->delete = Server_delete;
    sv->listen = Server_listen;
    // init server
    sv->set_ipaddr(sv, 127, 0, 0, 1);
    sv->set_port(sv, 8080);
    return sv;
}

void Server_set_handler(Server* sv, void (*handler)(ServerReq*, ServerRes*))
{
    if (!sv) server_print_err("null pointer", E_NULLPTR);
    if (!handler) server_print_err("null pointer", E_NULLPTR);
    sv->priv->handler = handler;
}

void Server_set_ipaddr(Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3)
{
    if (!sv) server_print_err("null pointer", E_NULLPTR);
    sv->priv->addr[0] = a0;
    sv->priv->addr[1] = a1;
    sv->priv->addr[2] = a2;
    sv->priv->addr[3] = a3;
}

void Server_set_port(Server* sv, port_t port)
{
    if (!sv) server_print_err("null pointer", E_NULLPTR);
    sv->priv->port = port;
}

void Server_listen(Server* sv, void (*callback)(ipaddr_t, port_t))
{
    if (!sv) server_print_err("null pointer", E_NULLPTR);
    sockfd_t hostfd = server_socket_listen(sv->priv->addr, sv->priv->port);
    const char* datetime = NULL;
    printf("[%s] - listening on %d.%d.%d.%d:%d\n",
        datetime = server_std_gettime(),
        sv->priv->addr[0],
        sv->priv->addr[1],
        sv->priv->addr[2],
        sv->priv->addr[3],
        sv->priv->port
    );
    free((void*) datetime);
    if (callback) callback(sv->priv->addr, sv->priv->port);
    while (!sigint_stop) {
        ServerReq* req = server_socket_accept(hostfd);
        // log request reciept
        if (req->size) {
            const char* datetime = NULL;
            printf("[%s] - %d.%d.%d.%d \"%.*s...\"\n",
                datetime = server_std_gettime(),
                req->addr[0], req->addr[1], req->addr[2], req->addr[3],
                server_std_get_sub_reqdata_end(req->data),
                req->data
            );
            free((void*) datetime);
        }
        // connection closed by client, drop request
        // note the || below, this if condition is not an inverse of the previous condition
        if (!req->clientfd || !req->size) {
            const char* datetime = NULL;
            printf("[%s] - %d.%d.%d.%d client closed connection\n",
                datetime = server_std_gettime(),
                req->addr[0], req->addr[1], req->addr[2], req->addr[3]
            );
            free((void*) datetime);
            req->delete(&req);
            continue;
        }
        ServerRes* res = ServerRes_new(req->clientfd);
        sv->priv->handler(req, res);
        req->delete(&req);
        res->delete(&res);
    }
    server_socket_close(hostfd);
    sv->delete(&sv);
}

void Server_delete(Server** sv)
{
    if (!sv && !*sv) return;
    free((*sv)->priv);
    free(*sv);
    *sv = NULL;
}
