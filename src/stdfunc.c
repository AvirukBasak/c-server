#include <stdlib.h>    // abort
#include <time.h>      // time_t, struct tm, time, localtime

#include "io.h"
#include "errcodes.h"
#include "stdfunc.h"

bool __server_std_is_litle_endian()
{
    uint8_t swaptest[2] = { 0, 1 };
    return (*(uint16_t*)swaptest);
}

char __server_std_to_hex(const uint8_t _4bits)
{
    const uint8_t bits4 = _4bits & 0x0f;
    if (bits4 >= 0x00 && bits4 <= 0x09) return bits4 + '0';
    else if (bits4 >= 0x0a && bits4 <= 0x0f) return bits4 - 0x0a + 'a';
    else abort();
}

const char* __server_std_gettime()
{
    const char* months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    char* nowtime_utc = malloc(strlen("YYYY-MM-DD HH:MM:SS +UTC") +1);
    if (!nowtime_utc) __server_print_err("null pointer", E_NULLPTR);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(nowtime_utc, "%04d-%s-%02d %02d:%02d:%02d",
        tm.tm_year +1900,
        months[tm.tm_mon],
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec
    );
    return nowtime_utc;
}

int __server_std_get_sub_reqdata_end(const char* reqdata)
{
    return (int) MIN(                          // get min of the following three positions
        MIN(
            32,                                // max 32, position of 32nd char
            strchr(reqdata, '\n') - reqdata    // position of \n in request
        ), strchr(reqdata, '\r') - reqdata     // position of \r in request
    );
}
