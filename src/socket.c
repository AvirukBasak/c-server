#include <stdio.h>      // fprintf
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

int server_socket_try(int retval, const char* msg) {
    if (retval <= -1)
        server_print_err(msg, E_ERRNO);
    else if (retval == STDOUT_FILENO || retval == STDERR_FILENO)
        server_print_err(msg, E_SOCKFD);
    return retval;
}

sockfd_t server_socket_listen(ipaddr_t addr, port_t port) {
    sockfd_t hostfd = server_socket_try(
        socket(AF_INET, SOCK_STREAM , 0),
        "socket creation failed"
    );
    int option = 1;
    // immediately reuse socket once server quits
    setsockopt(hostfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    sockaddrin_t hostaddr;
    memset(&hostaddr, 0, sizeof(hostaddr));
    hostaddr.sin_family = AF_INET;
    hostaddr.sin_addr.s_addr = *(uint32_t*) addr;
    hostaddr.sin_port = htons(port);
    server_socket_try(
        bind(hostfd, (sockaddr_t*) &hostaddr, sizeof(hostaddr)),
        "socket bind failed"
    );
    server_socket_try(
        listen(hostfd, SOCK_BACKLOG),
        "socket listen failed"
    );
    return hostfd;
}

ServerReq* server_socket_accept(sockfd_t hostfd)
{
    server_socket_try(hostfd, "host socket fd invalid");
    sockaddrin_t clientaddr;
    socklen_t len = sizeof(clientaddr);
    sockfd_t clientfd = server_socket_try(
        accept(hostfd, (sockaddr_t*) &clientaddr, &len),
        "socket accept failed"
    );
    ipaddr_t addr;
    uint32_t sin_addr = clientaddr.sin_addr.s_addr;
    addr[0] = ((uint8_t*) &sin_addr)[0];
    addr[1] = ((uint8_t*) &sin_addr)[1];
    addr[2] = ((uint8_t*) &sin_addr)[2];
    addr[3] = ((uint8_t*) &sin_addr)[3];
    return ServerReq_new(clientfd, addr);
}

void server_socket_close(sockfd_t sockfd)
{
    server_socket_try(sockfd, "socket fd invalid");
    close(sockfd);
}
