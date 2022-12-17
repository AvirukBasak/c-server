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

void write_data(ServerReq* req, ServerRes* res);
void write_time(ServerReq* req, ServerRes* res);

void conn_handler(ServerReq* req, ServerRes* res) {
    res->writef(res, "HTTP/1.1 OK\r\n");
    res->writef(res, "Content-Type: text/html\r\n");
    res->writef(res, "Server: tcp-server\r\n");
    res->writef(res, "\r\n");
    res->writef(res,
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "    <meta charset=\"utf-8\"/>\n"
        "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"/>\n"
        "    <meta name=\"keywords\" content=\"\"/>\n"
        "    <meta name=\"description\" content=\"\"/>\n"
        "    <meta name=\"viewport\" content=\"width=device-width, height=device-height, user-scalable=no\"/>\n"
        "    <title>Demo Server</title>\n"
        "    <style>\n"
        "        * {\n"
        "            font-size: 130%%;\n"
        "            font-family: monospace;\n"
        "        }\n"
        "        body {\n"
        "            margin: 10px;\n"
        "        }\n"
        "        pre {\n"
        "            width: 100%%;\n"
        "            overflow: scroll;\n"
        "        }\n"
        "        h1 {\n"
        "            font-size: 190%%;\n"
        "            font-family: monospace;\n"
        "        }\n"
        "    </style>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Recieved Data</h1>\n"
        "    <pre>\n"
    );
    write_data(req, res);
    res->writef(res, "\n");
    write_time(req, res);
    res->writef(res,
        "    </pre>\n"
        "</body>\n"
        "</html>\n"
        "\r\n"
    );
    res->writef(res, "\r\n");
    res->end(res);
}

void write_data(ServerReq* req, ServerRes* res) {
    char* data = malloc(1);
    size_t sz = 0;
    data[0] = 0;
    // read a full GET request, ends when line empty
    while (true) {
        char* line = req->readLine(req);
        data = realloc(data, (sz += req->size +1) +1);
        if (!req->size) {
            data[sz] = 0;
            break;
        }
        strcat(data, line);
        strcat(data, "\n");
    }
    res->writeBytes(res, data, sz);
    free(data);
}

void write_time(ServerReq* req, ServerRes* res) {
    const char* datetime = server_gettime();
    res->writef(res, "Server Time: %s\n", datetime);
    free((void*) datetime);
}
