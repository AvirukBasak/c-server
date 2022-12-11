#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include <inttypes.h> // uint64_t, int64_t

#include "types.h"

void __server_sockwrite_str(sockfd_t sockfd, const char* s);
void __server_sockwrite_ui64(sockfd_t sockfd, const uint64_t n);
void __server_sockwrite_i64(sockfd_t sockfd, const int64_t n);
void __server_sockwrite_ptr(sockfd_t sockfd, const void* p);

#endif
