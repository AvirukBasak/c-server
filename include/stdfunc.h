#ifndef __STDFUNC_H__
#define __STDFUNC_H__

#include <stdbool.h>    // bool
#include <inttypes.h>   // uint8_t, uint16_t

#define MIN(a,b) (a<b?a:b)

bool        server_std_is_litle_endian();
char        server_std_to_hex(const uint8_t _4bits);
const char* server_std_gettime();
int         server_std_get_sub_reqdata_end(const char* reqdata);

#endif
