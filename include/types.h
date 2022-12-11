#ifndef __TYPES_H__
#define __TYPES_H__

#include <arpa/inet.h>    // struct sockaddr, struct sockaddr_in

typedef uint8_t ipaddr_t[4];
typedef uint16_t port_t;

typedef int sockfd_t;
typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddrin_t;

typedef struct Server Server;
typedef struct ServerReq ServerReq;
typedef struct ServerRes ServerRes;

#endif
