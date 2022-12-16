#include "libserver.h"

/**
 * @brief Handles connection
 * @param req Server request
 * @param res Server response
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
    res->writef(res, "HTTP/1.1 OK\r\n");
    res->writef(res, "Content-Type: text/plain\r\n");
    res->writef(res, "\r\n");
    res->writef(res, "Hello, World!\r\n");
    res->writef(res, "\r\n");
    res->end(res);
}
