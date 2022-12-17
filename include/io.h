#ifndef __IO_H__
#define __IO_H__

#include "types.h"

void server_print_err(const char* msg, int err_code);
void server_print_connlog(ServerReq* req);
void server_print_connclose(ServerReq* req);

#endif
