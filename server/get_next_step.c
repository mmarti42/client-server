#include "serv.h"

uint64_t get_next_step(t_sub *s)
{
    if (ULLONG_MAX - s->step < s->curr_pos)
        s->curr_pos = 0;
    if (!s->curr_pos)
	    return (s->curr_pos = s->start_pos);
    return (s->curr_pos += s->step);
}