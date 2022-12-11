#include <string.h>    // strlen, strerror
#include <unistd.h>    // write
#include <errno.h>     // errno
#include <stdlib.h>    // exit, abort
#include <stdio.h>     // fprintf, stderr

#include "stdfunc.h"
#include "io.h"

void __server_print_str(int fd, const char *s)
{
    if (!s) return;
    size_t len = strlen(s);
    write(fd, s, len);
}

void __server_print_ui64(int fd, const uint64_t n)
{
    uint64_t nb = n;
    char s[21];
    s[20] = 0;    // null termination
    s[19] = '0';  // default number 0
    int i = 19;   // location from where string starts
    while (nb && i >= 0) {
        s[i--] = (nb % 10) + '0';
        nb /= 10;
    }
    if (i < 19) i++;
    __server_print_str(fd, &s[i]);
}

void __server_print_i64(int fd, const int64_t n)
{
    uint64_t nb = n < 0 ? -n : n;
    if (n < 0) __server_print_str(fd, "-");
    __server_print_ui64(fd, nb);
}

void __server_print_ptr(int fd, const void *p)
{
    char *b = (char*)(&p);
    char s[16];
    size_t len = 0;
    // most significant byte
    bool msbyte_zero = true;
    bool is_bend = __server_std_is_litle_endian();
    int i = is_bend ? 7 : 0;
    for (int j = 0; (is_bend ? (i >= 0) : (i < 8)) && j < 16;) {
        const uint8_t byte = b[i];
        char halfbyte0 = __server_std_to_hex(byte >> 4);
        char halfbyte1 = __server_std_to_hex(byte);
        if (halfbyte0 != '0' || halfbyte1 != '0')
            msbyte_zero = false;
        if (!msbyte_zero) {
            s[j] = halfbyte0;
            s[j+1] = halfbyte1;
            j+=2;
            len++;
        }
        is_bend ? i-- : i++;
    }
    write(fd, "0x", 2);
    if (len < 1) write(fd, "00", 2);
    else write(fd, s, 2*len);
}

void __server_print_err(const char *message, int err_code)
{
    if (!err_code && errno)
        fprintf(stderr, "libserver: %s: %s\n", message, strerror(errno));
    else
        fprintf(stderr, "libserver: error: %s\n", message);
#ifdef DEBUG
    abort();
#else
    exit(err_code ? err_code : errno);
#endif
}
