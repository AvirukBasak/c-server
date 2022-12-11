#include <strings.h>    // bzero

#include "errcodes.h"
#include "io.h"
#include "server.h"
#include "socket.h"

sockdesc_t __server_socket_new(ipaddr_t addr, port_t port) {
    sockdesc_t sd = socket(AF_INET , SOCK_STREAM , 0);
    if (sd < -1) __server_print_err("socket_new failed", E_ERRNO);
    sockaddrin_t saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    return sd;
}
