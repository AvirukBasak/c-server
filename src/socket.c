#include <string.h>     // memset
#include <inttypes.h>   // uint32_t
#include <unistd.h>     // close
#include <sys/socket.h> // socket, bind, listen, accept, recv, send
#include <arpa/inet.h>  // struct sockaddr, struct sockaddr_in, htonl, htons

#include "socket.h"
#include "errcodes.h"
#include "io.h"
#include "request.h"

int server_socket_die(int retval, const char* msg) {
    if (retval <= -1)
        server_print_err(msg, E_ERRNO);
    else if (retval == STDOUT_FILENO || retval == STDERR_FILENO)
        server_print_err(msg, E_SOCKFD);
    return retval;
}

bool server_socket_isvalid(sockfd_t sockfd) {
    if (sockfd <= 0
     || sockfd == STDIN_FILENO
     || sockfd == STDOUT_FILENO
     || sockfd == STDERR_FILENO) return false;
    return true;
}

sockfd_t server_socket_listen(ipaddr_t addr, port_t port) {
    sockfd_t hostfd = server_socket_die(
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
    server_socket_die(
        bind(hostfd, (sockaddr_t*) &hostaddr, sizeof(hostaddr)),
        "socket bind failed"
    );
    server_socket_die(
        listen(hostfd, SOCK_BACKLOG),
        "socket listen failed"
    );
    return hostfd;
}

ServerReq* server_socket_accept(sockfd_t hostfd)
{
    if (!server_socket_isvalid(hostfd)) return NULL;
    sockaddrin_t clientaddr;
    socklen_t len = sizeof(clientaddr);
    sockfd_t clientfd = accept(hostfd, (sockaddr_t*) &clientaddr, &len);
    if (!server_socket_isvalid(clientfd)) return NULL;
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
    if (!server_socket_isvalid(sockfd))
        return;
    close(sockfd);
}
