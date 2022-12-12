#include <stdlib.h>    // malloc
#include <unistd.h>    // close
#include <stdbool.h>   // bool

#include "errcodes.h"
#include "io.h"
#include "response.h"
#include "socketio.h"

ServerRes* ServerRes_new(sockfd_t clientfd)
{
    ServerRes* res = malloc(sizeof(ServerRes));
    if (!res) server_print_err("null pointer", E_NULLPTR);
    server_socket_try(clientfd, "client socket fd invalid");
    res->clientfd = clientfd;
    res->writeBytes = ServerRes_writeBytes;
    res->writeStr = ServerRes_writeStr;
    res->writeU64 = ServerRes_writeU64;
    res->writeI64 = ServerRes_writeI64;
    res->writeHex = ServerRes_writeHex;
    res->end = ServerRes_end;
    res->delete = ServerRes_delete;
    return res;
}

void ServerRes_delete(ServerRes** res)
{
    if (!res && !*res) return;
    if ((*res)->clientfd >= 0) {
        server_socket_try((*res)->clientfd, "client socket fd invalid");
        close((*res)->clientfd);
    }
    free(*res);
    *res = NULL;
}

void ServerRes_writeBytes(ServerRes* res, const char* data, size_t size)
{
    server_socket_try(res->clientfd, "client socket fd invalid");
    write(res->clientfd, data, size);
}

void ServerRes_writeStr(ServerRes* res, const char* str)
{
    server_socket_try(res->clientfd, "client socket fd invalid");
    server_sockwrite_str(res->clientfd, str);
}

void ServerRes_writeU64(ServerRes* res, uint64_t n)
{
    server_socket_try(res->clientfd, "client socket fd invalid");
    server_sockwrite_ui64(res->clientfd, n);
}

void ServerRes_writeI64(ServerRes* res, int64_t n)
{
    server_socket_try(res->clientfd, "client socket fd invalid");
    server_sockwrite_i64(res->clientfd, n);
}

void ServerRes_writeHex(ServerRes* res, uint64_t n)
{
    server_socket_try(res->clientfd, "client socket fd invalid");
    server_sockwrite_ptr(res->clientfd, (void*) n);
}

void ServerRes_end(ServerRes* res)
{
    if (res->clientfd < 0) return;
    server_socket_try(res->clientfd, "client socket fd invalid");
    close(res->clientfd);
    res->clientfd = -1;
}
