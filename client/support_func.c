#include "client.h"

int ft_isdigit(char c)
{
    if (c < '0' || c > '9')
        return (1);
    return (0);
}

void err_quit(char *s)
{
    if (s)
        fprintf(stderr, "%s\n", s);
    else
        perror("server");
    exit (1);
}

void    free_dar(uint64_t **all_data)
{
    uint64_t **tmp;

    tmp = all_data;
    while (*tmp)
    {
        free(*tmp);
        tmp++;
    }
    free (all_data);
}

void    *xmalloc(size_t size)
{
    void *new;

    if (!(new = malloc(size)))
        err_quit(NULL);
    memset(new, 0, size);
    return (new);
}
size_t     darlen(uint64_t **m)
{
    size_t i = 0;

    if (!m)
        return (0);
    while (*m)
    {
        m++;
        i++;
    }
    return (i);
}

void print_data(uint64_t **all_data)
{
    char *format;

    format = ft_strjoin("%", PRIu64);
    while (*all_data)
    {
        int i = 0;
        while (i < 3)
        {
            printf(format, (*all_data)[i++]);
            printf(" ");
        }
        printf("\n");
        all_data++;
    }
    free(format);
}

void    print_socket(int sockfd)
{
    uint64_t a;
    int b = 10;
    char *format;

    format = ft_strjoin("%", PRIu64);
    while (b--)
    {
        read(sockfd, &a, sizeof(uint64_t));
        if (!a)
            err_quit("Connection failed");
        convert(a);
        printf(format, a);
        printf(" ");
    }
    free (format);
    printf("\n");
}
