#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "stdhead.h"

typedef struct ServerReq ServerReq;

struct ServerReq {
    char* data;
    size_t size;
};

#endif
