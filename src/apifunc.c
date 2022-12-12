#include "apifunc.h"
#include "stdfunc.h"

const char* server_gettime() {
    return __server_std_gettime();
}
