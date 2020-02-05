#include "serv.h"

void		convert(uint64_t tmp)
{
	if (IS_BE)
        return ;
	tmp = (((uint64_t)ntohl(tmp)) << 32) + ntohl(tmp >> 32);
}