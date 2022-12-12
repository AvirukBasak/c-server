#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/socket.h>    // socket, bind, listen, accept, recv, send
#include <arpa/inet.h>     // struct sockaddr, struct sockaddr_in, htonl, htons

#include "types.h"
#include "server.h"
#include "request.h"

#define SOCK_BACKLOG (100)
#define SOCK_RECVLEN (4096)

int __server_socket_try(int retval, const char* msg);
void __server_socket_sigpipe_handler(int signum);
sockfd_t __server_socket_listen(ipaddr_t addr, port_t port);
ServerReq* __server_socket_accept(sockfd_t hostfd);
void __server_socket_close(sockfd_t sockfd);

#endif
