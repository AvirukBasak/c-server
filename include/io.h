#ifndef __IO_H__
#define __IO_H__

#include <inttypes.h> // uint64_t, int64_t

void __server_print_str(int fd, const char* s);
void __server_print_ui64(int fd, const uint64_t n);
void __server_print_i64(int fd, const int64_t n);
void __server_print_ptr(int fd, const void* p);
void __server_print_err(const char* msg, int err_code);

#endif
