#include <stdio.h>

#include "libserver.h"

void conn_handler(ServerReq* req, ServerRes* res) {
    res->writeStr(res, "HTTP/1.1 OK\r\n\r\n");
    res->writeStr(res, "Recieved data:<html><body><pre>\r\n");
    res->writeBytes(res, req->data, req->size);
    res->writeStr(res, "</pre></body></html>\r\n...truncated\r\n\r\n");
    res->send(res);
}

void start(ipaddr_t a, port_t p) {
    printf("Server listening at %d.%d.%d.%d:%d\n", a[0], a[1], a[2], a[3], p);
}

int main(int argc, char *argv[])
{
    Server* sv = Server_new();
    sv->set_handler(sv, conn_handler);
    sv->set_ipaddr(sv, 0, 0, 0, 0);
    sv->set_port(sv, 42069);
    sv->listen(sv, start);
    return 0;
}
