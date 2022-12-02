#ifndef __IO_H__
#define __IO_H__

#include "stdhead.h"

void __server_print_str(int fd, const char *s);
void __server_print_ui64(int fd, const ui64_t n);
void __server_print_i64(int fd, const i64_t n);
void __server_print_ptr(int fd, const ptr_t p);
void __server_print_err(const char *s);

#endif
