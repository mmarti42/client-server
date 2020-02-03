#include "serv.h"

static void	push_back(t_sub **sub_list, uint64_t *arr)
{
    static t_sub *curr;

    if (!*sub_list)
    {
        *sub_list = (t_sub *)xmalloc(sizeof(t_sub));
        curr = *sub_list;
    }
    else
    {
        curr->next = (t_sub *)xmalloc(sizeof(t_sub));
        curr = curr->next;
    }
    curr->start_pos = *arr;
    curr->step = arr[1];
}

t_sub		*parse_sub(uint64_t **arr)
{
    t_sub *sub_list = NULL;

    while (*arr)
    {
        push_back(&sub_list, *arr);
        arr++;
    }
    return (sub_list);
}