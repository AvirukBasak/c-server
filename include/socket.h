#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/socket.h>
#include <arpa/inet.h>

#include "server.h"

#define SOCK_BACKLOG (100)

typedef int sockfd_t;
typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddrin_t;

int __server_socket_try(int retval, const char* msg);
sockfd_t __server_socket_listen(ipaddr_t addr, port_t port);
char* __server_socket_accept(sockfd_t hostfd);
void __server_socket_close(sockfd_t sockfd);

#endif
