#include "client.h"

static void		ft_swap(uint64_t **a, uint64_t **b)
{
    uint64_t *c;

    c = *a;
    *a = *b;
    *b = c;
}

void			bubble_sort(uint64_t **a)
{
    uint64_t **tmp;
    int f = 0;
	size_t it = darlen(a) - 1;
	
    while (it--)
    {
        tmp = a;
        while (*(tmp + 1))
        {
            if (**tmp > **(tmp + 1))
            {
                ft_swap(&*tmp, &*(tmp + 1));
                f = 1;
            }
            tmp++;
        }
        if (!f)
            break ;
    }
}
