#include "serv.h"

void	print_seq(uint64_t **seq)
{
	while (*seq)
	{
		for(int i = 0; i < 2; i++)
			printf("%llu ", (*seq)[i]);
		seq++;
		printf("\n");
	}
}

void    *xmalloc(size_t size)
{
    void *new;

    if (!(new = malloc(size)))
        err_exit(NULL);
    memset(new, 0, size);
    return (new);
}

void    err_exit(char *s)
{
    if (s)
        printf("%s\n", s);
    else
       perror ("server");
    exit (1);
}