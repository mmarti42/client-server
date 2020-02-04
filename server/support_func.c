#include "serv.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	dst = (char *)xmalloc(strlen(s1) + strlen(s2) + 1);
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	return (dst);
}

void	print_seq(uint64_t **seq)
{
    char *format;

    format = ft_strjoin("%", PRIu64);
	while (*seq)
	{
		for(int i = 0; i < 2; i++)
        {
			printf(format, (*seq)[i]);
            printf(" ");
        }
		seq++;
		printf("\n");
	}
    free(format);
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