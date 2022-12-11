#include <stdlib.h>    // malloc
#include <stdbool.h>   // bool

#include "errcodes.h"
#include "io.h"
#include "request.h"

ServerReq* ServerReq_new()
{
    ServerReq* req = malloc(sizeof(ServerReq));
    if (!req) __server_print_err("null pointer", E_NULLPTR);
    req->delete = ServerReq_delete;
    return req;
}

void ServerReq_delete(ServerReq** req)
{
    if (!req && !*req) return;
    // free((*req)->priv);
    free(*req);
    *req = NULL;
}
