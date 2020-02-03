#include "client.h"

static int		check_nums(char *s)
{
    while (*s)
    {
        if (ft_isdigit(*s))
            return (-1);
        s++;
    }
    return (0);
}

static uint64_t	get_seq_num(char *s)
{
    char *tmp;

    if (!s || strncmp(s, "seq", 3))
        return (0);
    s += 3;
    if (check_nums(s) < 0)
        return (0);
    return (strtoull(s, NULL, 10));
}

static uint64_t	get_start_pos(char *s)
{
    if (!s || check_nums(s) < 0)
        return (0);
    return (strtoull(s, NULL, 10));
}

static uint64_t	get_step(char *s)
{
    return (get_start_pos(s));
}

int				parse_string(char *input, uint64_t **data)
{
    (*data) = (uint64_t *)xmalloc(sizeof(uint64_t) * 3);
    (*data)[0] = get_seq_num(strtok(input, " \t"));
    (*data)[1] = get_start_pos(strtok(NULL, " \t"));
    (*data)[2] = get_step(strtok(NULL, " \t"));
    if (!(*data)[0] || !(*data)[1] || !(*data)[2])
    {
        memset(*data, 0, sizeof(uint64_t) * 3);
        fprintf(stderr, "client: invalid input\n");
        return (-1);
    }
    return (0);
}