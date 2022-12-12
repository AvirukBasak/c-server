#ifndef __STDFUNC_H__
#define __STDFUNC_H__

#include <stdbool.h>    // bool
#include <inttypes.h>   // uint8_t, uint16_t

bool __server_std_is_litle_endian();
char __server_std_to_hex(const uint8_t _4bits);
const char* __server_std_gettime();

#endif
