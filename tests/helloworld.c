#include "libserver.h"

/**
 * @brief Handles connection.
 * Echoes entire request w/ headers and all back to the client.
 * @param req Server request.
 * @param res Server response.
 */
void conn_handler(ServerReq* req, ServerRes* res);

int main(int argc, char *argv[])
{
    Server* sv = Server_new();
    sv->set_handler(sv, conn_handler);
    sv->listen(sv, NULL);
    return 0;
}

void conn_handler(ServerReq* req, ServerRes* res) {
    res->writeStr(res, "HTTP/1.1 OK\r\n");
    res->writeStr(res, "Content-Type: text/plain\r\n");
    res->writeStr(res, "\r\n");
    res->writeStr(res, "Hello, World!\r\n");
    res->writeStr(res, "\r\n");
    res->end(res);
}
