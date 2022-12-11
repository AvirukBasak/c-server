#include <stdlib.h>    // malloc
#include <stdbool.h>   // bool

#include "types.h"
#include "errcodes.h"
#include "io.h"
#include "server.h"
#include "socket.h"
#include "request.h"

ServerReq* ServerReq_new(
    char *data,         // request data
    size_t size,        // request data size
    sockfd_t clientfd,  // clientfd, response destination
    ipaddr_t addr       // client ip address
) {
    ServerReq* req = malloc(sizeof(ServerReq));
    if (!req) __server_print_err("null pointer", E_NULLPTR);
    req->delete = ServerReq_delete;
    req->data = data;
    req->size = size;
    __server_socket_try(clientfd, "client socket fd invalid");
    req->clientfd = clientfd;
    req->addr[0] = addr[0];
    req->addr[1] = addr[1];
    req->addr[2] = addr[2];
    req->addr[3] = addr[3];
    return req;
}

void ServerReq_delete(ServerReq** req)
{
    if (!req && !*req) return;
    free((*req)->data);
    free(*req);
    *req = NULL;
}
