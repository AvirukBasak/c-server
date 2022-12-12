#include <string.h>      // strlen, strerror
#include <sys/socket.h>  // send

#include "types.h"
#include "socketio.h"
#include "stdfunc.h"

void server_sockwrite_str(sockfd_t sockfd, const char* s)
{
    if (!s) return;
    size_t len = strlen(s);
    send(sockfd, s, len, 0);
}

void server_sockwrite_ui64(sockfd_t sockfd, const uint64_t n)
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
    server_sockwrite_str(sockfd, &s[i]);
}

void server_sockwrite_i64(sockfd_t sockfd, const int64_t n)
{
    uint64_t nb = n < 0 ? -n : n;
    if (n < 0) server_sockwrite_str(sockfd, "-");
    server_sockwrite_ui64(sockfd, nb);
}

void server_sockwrite_ptr(sockfd_t sockfd, const void* p)
{
    char* b = (char*)(&p);
    char s[16];
    size_t len = 0;
    // most significant byte
    bool msbyte_zero = true;
    bool is_liend = server_std_is_litle_endian();
    int i = is_liend ? 7 : 0;
    for (int j = 0; (is_liend ? (i >= 0) : (i < 8)) && j < 16;) {
        const uint8_t byte = b[i];
        char halfbyte0 = server_std_to_hex(byte >> 4);
        char halfbyte1 = server_std_to_hex(byte);
        if (halfbyte0 != '0' || halfbyte1 != '0')
            msbyte_zero = false;
        if (!msbyte_zero) {
            s[j] = halfbyte0;
            s[j+1] = halfbyte1;
            j+=2;
            len++;
        }
        is_liend ? i-- : i++;
    }
    send(sockfd, "0x", 2, 0);
    if (len < 1) send(sockfd, "00", 2, 0);
    else send(sockfd, s, 2*len, 0);
}
