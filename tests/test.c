#include <stdio.h>

#include "libserver.h"

void conn_handler(ServerReq* req, ServerRes* res) {
    res->writeStr(res, "HTTP/1.1 OK\r\n\r\n");
    res->writeStr(res,
        "<html>\n"
        "<head>\n"
        "    <meta charset=\"utf-8\">\n"
        "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
        "    <meta name=\"keywords\" content=\"\">\n"
        "    <meta name=\"description\" content=\"\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, height=device-height, user-scalable=no\">\n"
        "    <title>Demo</title>\n"
        "</head>\n"
        "<body>\n"
        "    <pre>\n"
        "Recieved data:\n"
    );
    res->writeBytes(res, req->data, req->size);
    res->writeStr(res,
        "...truncated\n"
        "    </pre>\n"
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
