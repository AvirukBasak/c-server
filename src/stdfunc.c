#include <stdlib.h>    // abort

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
