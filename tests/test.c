#include <stdio.h>

#include "libserver.h"

void listener(ServerReq* req, ServerRes* res) {
    res->writeStr(res, "HTTP/1.1 OK\r\n\r\n");
    res->writeStr(res, "Recieved data:<html><body><pre>\r\n");
    res->writeBytes(res, req->data, req->size);
    res->writeStr(res, "</pre></body></html>\r\n...truncated\r\n\r\n");
    res->send(res);
}

void listenerStart(Server* sv) {
    ip4addr_t a = sv->ip4_addr;
    port_t p = sv->port;
    printf("server running at %d.%d.%d.%d:%d\n", a[0], a[1], a[2], a[3], p);
}

int main(int argc, char *argv[])
{
    Server* sv = Server_new();
    sv->listener = listener;
    // note: if one addr is NULL, other is used
    // if both NULL, ipv4 0.0.0.0 is used
    // if both set, ipv4 is used
    sv->ip4_addr = { 0, 0, 0, 0 };
    server->port = 42069;
    sv->listen(sv, listenerStart);
    return 0;
}
