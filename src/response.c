#include <stdlib.h>    // malloc
#include <stdbool.h>   // bool

#include "errcodes.h"
#include "io.h"
#include "response.h"

ServerRes* ServerRes_new()
{
    ServerRes* res = malloc(sizeof(ServerRes));
    if (!res) __server_print_err("null pointer", E_NULLPTR);
    res->writeBytes = ServerRes_writeBytes;
    res->writeStr = ServerRes_writeStr;
    res->writeU64 = ServerRes_writeU64;
    res->writeI64 = ServerRes_writeI64;
    res->writeHex = ServerRes_writeHex;
    res->send = ServerRes_send;
    res->delete = ServerRes_delete;
    return res;
}

void ServerRes_delete(ServerRes** res)
{
    if (!res && !*res) return;
    // free((*res)->priv);
    free(*res);
    *res = NULL;
}

void ServerRes_writeBytes(ServerRes* res, const char* data, size_t size)
{}

void ServerRes_writeStr(ServerRes* res, const char* str)
{}

void ServerRes_writeU64(ServerRes* res, uint64_t n)
{}

void ServerRes_writeI64(ServerRes* res, int64_t n)
{}

void ServerRes_writeHex(ServerRes* res, const void* p)
{}

void ServerRes_send(ServerRes* res)
{}
