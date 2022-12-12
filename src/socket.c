#include <string.h>     // memset, strncmp
#include <stdlib.h>     // realloc
#include <inttypes.h>   // uint32_t
#include <unistd.h>     // close
#include <stdbool.h>    // bool

#include "types.h"
#include "errcodes.h"
#include "io.h"
#include "request.h"
#include "server.h"
#include "socket.h"

int __server_socket_try(int retval, const char* msg) {
    if (retval <= -1
        || retval == STDOUT_FILENO
        || retval == STDERR_FILENO)
            __server_print_err(msg, E_ERRNO);
    return retval;
}

sockfd_t __server_socket_listen(ipaddr_t addr, port_t port) {
    sockfd_t hostfd = __server_socket_try(
        socket(AF_INET, SOCK_STREAM , 0),
        "socket creation failed"
    );
    sockaddrin_t hostaddr;
    memset(&hostaddr, 0, sizeof(hostaddr));
    hostaddr.sin_family = AF_INET;
    hostaddr.sin_addr.s_addr = *(uint32_t*) addr;
    hostaddr.sin_port = htons(port);
    __server_socket_try(
        bind(hostfd, (sockaddr_t*) &hostaddr, sizeof(hostaddr)),
        "socket bind failed"
    );
    __server_socket_try(
        listen(hostfd, SOCK_BACKLOG),
        "socket listen failed"
    );
    return hostfd;
}

ServerReq* __server_socket_accept(sockfd_t hostfd)
{
    __server_socket_try(hostfd, "host socket fd invalid");
    sockaddrin_t clientaddr;
    socklen_t len = sizeof(clientaddr);
    sockfd_t clientfd = __server_socket_try(
        accept(hostfd, (sockaddr_t*) &clientaddr, &len),
        "socket accept failed"
    );
    ipaddr_t addr;
    uint32_t sin_addr = clientaddr.sin_addr.s_addr;
    addr[0] = ((uint8_t*) &sin_addr)[0];
    addr[1] = ((uint8_t*) &sin_addr)[1];
    addr[2] = ((uint8_t*) &sin_addr)[2];
    addr[3] = ((uint8_t*) &sin_addr)[3];
    char* data = NULL;
    size_t data_sz = 0;
    bool endreq = false;
    do {
        char buffer[SOCK_RECVLEN +1];
        size_t sz = recv(clientfd, buffer, SOCK_RECVLEN, 0);
        buffer[sz] = 0;
        if (!sz) break;
        if (sz == 1 && buffer[0] == 0) endreq = true;                  // null
        if (sz == 1 && buffer[0] == '\n') endreq = true;               // new line
        if (sz == 2 && !strcmp("\r\n", buffer)) endreq = true;         // http request end
        if (sz == 1 && (signed char) buffer[0] == EOF) endreq = true;  // end of file
        data = realloc(data, data_sz +sz +1);
        memcpy(&data[data_sz], buffer, sz);
        data_sz += sz;
        data[data_sz] = 0;
    } while(!endreq);
    return ServerReq_new(data, data_sz, clientfd, addr);
}

void __server_socket_close(sockfd_t sockfd)
{
    __server_socket_try(sockfd, "socket fd invalid");
    close(sockfd);
}
