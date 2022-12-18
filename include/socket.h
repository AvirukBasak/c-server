#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdbool.h>

#include "types.h"
#include "request.h"

#define SOCK_BACKLOG (100)
#define SOCK_RECVLEN (4 * 4096)

int        server_socket_die     (int retval, const char* msg);
bool       server_socket_isvalid (sockfd_t sockfd);
sockfd_t   server_socket_listen  (ipaddr_t addr, port_t port);
ServerReq* server_socket_accept  (sockfd_t hostfd);
void       server_socket_close   (sockfd_t sockfd);

#endif
