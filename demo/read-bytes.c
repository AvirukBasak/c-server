#include <stdlib.h>    // free

#include "libserver.h"

/**
 * @brief Handles connection.
 * Echoes entire request w/ headers and all back to the client.
 * @param req Server request
 * @param res Server response
 */
void conn_handler(ServerReq* req, ServerRes* res);

int main(int argc, char *argv[])
{
    Server* sv = Server_new();
    sv->set_handler(sv, conn_handler);
    sv->set_ipaddr(sv, 0, 0, 0, 0);
    sv->set_port(sv, 8080);
    sv->listen(sv, NULL);
    return 0;
}

void conn_handler(ServerReq* req, ServerRes* res) {
    res->writef(res, "Enter 5 characters: ");
    char* s = req->readBytes(req, 5);
    res->writef(res, "You entered: %s\n", s);
    res->end(res);
}
