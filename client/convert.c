#include "client.h"

void    convert(uint64_t tmp)
{
    if (IS_BE)
        return ;
    tmp = (((uint64_t)htonl(tmp)) << 32) + htonl(tmp >> 32);
}