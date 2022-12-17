#include <stdio.h>
#include <string.h>

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
    // read a full GET request, ends when line empty
    while (true) {
        char* line = req->readLine(req);
        if (!strcmp(line, "")) break;
    }
    res->writef(res, "HTTP/1.1 OK\r\n");
    res->writef(res, "Content-Type: text/plain\r\n");
    res->writef(res, "\r\n");
    res->writef(res, "Hello, World!\r\n");
    res->writef(res, "\r\n");
    res->end(res);
}
