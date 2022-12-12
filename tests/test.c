#include <stdio.h>

#include "libserver.h"

void conn_handler(ServerReq* req, ServerRes* res) {
    res->writeStr(res, "HTTP/1.1 OK\r\n\r\n");
    res->writeStr(res,
        "<html>\n"
        "<body>\n"
        "    <pre>recieved data: "
    );
    res->writeBytes(res, req->data, req->size);
    res->writeStr(res,
        "...truncated</pre>\n"
        "</body>\n"
        "</html>\n"
        "\r\n\r\n"
    );
    res->send(res);
}

int main(int argc, char *argv[])
{
    Server* sv = Server_new();
    sv->set_handler(sv, conn_handler);
    sv->set_ipaddr(sv, 0, 0, 0, 0);
    sv->set_port(sv, 8080);
    sv->listen(sv, NULL);
    return 0;
}
